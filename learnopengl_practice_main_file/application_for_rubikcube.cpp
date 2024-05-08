#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader_s.h"
#include "camera.h"
#include "model.h"
#include "MakeCube.h"

#include <iostream>
#include <unordered_map>
#include <vector>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
unsigned int loadTexture(const char* path);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

float lastX = (float)SCR_WIDTH / 2.0f, lastY = (float)SCR_HEIGHT / 2.0f;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// initial setting
char sideMove;
bool isMoving = false;
bool changeDirection = false;
bool solving = false;
bool breath = false;
bool rubiks = false;
bool rotar = false;


int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Rubik Cube", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile shaders
    // -------------------------
    Shader ourshader("rubikcube.vs", "rubikcube.fs");

    // menu
    cout << "\t\tWELCOME TO RUBIK CUBE\n";
    cout << "Keys to move:" << "\n\t - MOUSE -> CAMERA" << "\n\t - UP arrow -> UP(U)" << "\n\t - DOWN arrow -> DOWN(D)";
    cout << "\n\t - LEFT arrow -> LEFT(L)" << "\n\t - RIGHT arrow -> RIGHT(R)";
    cout << "\n\t - F -> FRONT(F)" << "\n\t - B -> BACK(B)" << "\n\t - (Right) SHIFT -> CHANGE TO CLOCKWISE OR TO ANTICLOCKWISE";
    cout << "\nAnimation: " << "\n\t - R -> BREATH(START ANIMATION)" << "\n\t - S -> SOLVE (SMALL CUBE WILL FALL)";
    cout << "\nSHUFFLE: ";

    Rubik rubik(window, &ourshader, 0.2f);
    Rubik newRubiks[4] = { Rubik(window, &ourshader, 0.05f),Rubik(window, &ourshader, 0.05f) ,Rubik(window, &ourshader, 0.05f) ,Rubik(window, &ourshader, 0.05f) };
    Rubik* rubik2 = nullptr;
    int numRubik = 0;

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.8f, 0.8f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        ourshader.setMat4("projection", projection);

        glm::mat4 view = camera.GetViewMatrix();
        ourshader.setMat4("view", view);    

        if (solving == true) {
            Rubik* rubikMoving = &rubik;
            Rubik* rubikStatic = nullptr;
            if (rubiks) {
                rubikMoving = rubik2;
                rubikStatic = &rubik;
            }
            rubikMoving->setSolve();

            solving = false;
            if (rubikStatic) {
                rubikMoving->vibrate();
                rubikStatic->magnet();
                rubiks = false;
            }
        }

        else if (breath) {
            rubik.expand();
            breath = false;
            rubik2 = &newRubiks[numRubik];
            numRubik++;
            rubik2->brothers = rubik.brothers;
            rubik2->brothers.push_back(&rubik);
            rubik.brothers.push_back(rubik2);
            rubiks = true;
            rotar = true;
        }
        else if (rotar) {
            if (isMoving == false && changeDirection) {
                changeDirection = false;
                rubik2->degrees *= -1;
            }
            if (isMoving) {
                rubik2->fillShuffle(sideMove);
                rubik2->move(sideMove);
                isMoving = false;
                for (int i = 0; rubik2->degrees == 1.0f && i < 2; i++) {
                    rubik2->updateParts(sideMove);
                }
                rubik2->updateParts(sideMove);
            }
            rubik2->twist();
            rubik2->timesTwist++;
            if (rubik2->timesTwist == 40) rotar = false;
        }

        else if (isMoving == false && changeDirection) {
            changeDirection = false;
            if (rubiks) rubik2->degrees *= -1;
            else rubik.degrees *= -1;
        }

        else if (isMoving == true) {
            Rubik* rubikMoving = &rubik;
            Rubik* rubikStatic = nullptr;
            if (rubiks) {
                rubikMoving = rubik2;
                rubikStatic = &rubik;
            }
            rubikMoving->fillShuffle(sideMove);
            rubikMoving->move(sideMove);
            isMoving = false;
            for (int i = 0; rubikMoving->degrees == 1.0f && i < 2; i++) {
                rubikMoving->updateParts(sideMove);
            }
            rubikMoving->updateParts(sideMove);
        }
        else {
            rubik.draw();
        }


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        //glfwSwapBuffers(window);
        //glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------

    rubik.deleteBuffers();
    for (int i = 0; i < 4; i++)
    {
        newRubiks[i].deleteBuffers();
    }

    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
    if (!isMoving) {
        if (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS) {
            changeDirection = true;
        }
        if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
            isMoving = true;
            sideMove = 'U';
        }
        if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
            isMoving = true;
            sideMove = 'L';
        }
        if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
            isMoving = true;
            sideMove = 'R';
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            isMoving = true;
            sideMove = 'D';
        }
        if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
            isMoving = true;
            sideMove = 'F';
        }
        if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
            isMoving = true;
            sideMove = 'B';
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && !rotar) {
            solving = true;
        }
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}


// utility function for loading a 2D texture from file
// ---------------------------------------------------
unsigned int loadTexture(char const* path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}