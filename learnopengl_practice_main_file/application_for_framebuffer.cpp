//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//#include "stb_image.h"
//
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//
//#include "shader_s.h"
//#include "camera.h"
//#include "model.h"
//
//#include <iostream>
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void processInput(GLFWwindow* window);
//unsigned int loadTexture(const char* path);
//
//// settings
//const unsigned int SCR_WIDTH = 800;
//const unsigned int SCR_HEIGHT = 600;
//
//// camera
//Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);
//float lastX = (float)SCR_WIDTH / 2.0;
//float lastY = (float)SCR_HEIGHT / 2.0;
//bool firstMouse = true;
//
//// timing
//float deltaTime = 0.0f;
//float lastFrame = 0.0f;
//
//int main()
//{
//    // glfw: initialize and configure
//    // ------------------------------
//    glfwInit();
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//
//#ifdef __APPLE__
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//#endif
//
//    // glfw window creation
//    // --------------------
//    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
//    if (window == NULL)
//    {
//        std::cout << "Failed to create GLFW window" << std::endl;
//        glfwTerminate();
//        return -1;
//    }
//    glfwMakeContextCurrent(window);
//    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//    glfwSetCursorPosCallback(window, mouse_callback);
//    glfwSetScrollCallback(window, scroll_callback);
//
//    // tell GLFW to capture our mouse
//    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//
//    // glad: load all OpenGL function pointers
//    // ---------------------------------------
//    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//    {
//        std::cout << "Failed to initialize GLAD" << std::endl;
//        return -1;
//    }
//
//    // configure global opengl state
//    // -----------------------------
//    glEnable(GL_DEPTH_TEST);
//    glDepthFunc(GL_LESS); // always pass the depth test (same effect as glDisable(GL_DEPTH_TEST))
//
//    // build and compile shaders
//    // -------------------------
//    Shader shader("1.1.depth_testing.vs", "1.1.depth_testing.fs");
//    Shader screenshader("1.5. framebuffer_screen.vs", "1.5. framebuffer_screen.fs");
//
//    // set up vertex data (and buffer(s)) and configure vertex attributes
//    // ------------------------------------------------------------------
//    float cubeVertices[] = {
//        // Back face
//        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom-left
//         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
//         0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // bottom-right         
//         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right
//        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // bottom-left
//        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
//        // Front face
//        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
//         0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
//         0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
//         0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // top-right
//        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // top-left
//        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left
//        // Left face
//        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
//        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-left
//        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
//        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-left
//        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
//        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-right
//        // Right face
//         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
//         0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
//         0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right         
//         0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // bottom-right
//         0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // top-left
//         0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-left     
//         // Bottom face
//         -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
//          0.5f, -0.5f, -0.5f,  1.0f, 1.0f, // top-left
//          0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
//          0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // bottom-left
//         -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // bottom-right
//         -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, // top-right
//         // Top face
//         -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
//          0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
//          0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // top-right     
//          0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // bottom-right
//         -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // top-left
//         -0.5f,  0.5f,  0.5f,  0.0f, 0.0f  // bottom-left        
//    };
//    float planeVertices[] = {
//        // positions          // texture Coords (note we set these higher than 1 (together with GL_REPEAT as texture wrapping mode). this will cause the floor texture to repeat)
//         5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
//        -5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
//        -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
//
//         5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
//        -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
//         5.0f, -0.5f, -5.0f,  2.0f, 2.0f
//    };
//    // ֡���棺��һ�������ӵ�֡���棬�����е���Ⱦָ�д�뵽�����У������������Ƶ�����������ʾ����
//    float quadVertices[] = {  // һ�����ǵ�������Ļ��������
//        // positions   // texCoords
//        -1.0f,  1.0f,  0.0f, 1.0f,
//        -1.0f, -1.0f,  0.0f, 0.0f,
//         1.0f, -1.0f,  1.0f, 0.0f,
//
//        -1.0f,  1.0f,  0.0f, 1.0f,
//         1.0f, -1.0f,  1.0f, 0.0f,
//         1.0f,  1.0f,  1.0f, 1.0f
//    };
//    // cube VAO
//    unsigned int cubeVAO, cubeVBO;
//    glGenVertexArrays(1, &cubeVAO);
//    glGenBuffers(1, &cubeVBO);
//    glBindVertexArray(cubeVAO);
//    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), &cubeVertices, GL_STATIC_DRAW);
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(1);
//    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
//    glBindVertexArray(0);
//    // plane VAO
//    unsigned int planeVAO, planeVBO;
//    glGenVertexArrays(1, &planeVAO);
//    glGenBuffers(1, &planeVBO);
//    glBindVertexArray(planeVAO);
//    glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), &planeVertices, GL_STATIC_DRAW);
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(1);
//    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
//    glBindVertexArray(0);
//    // quad VAO
//    unsigned int quadVAO, quadVBO;
//    glGenVertexArrays(1, &quadVAO);
//    glGenBuffers(1, &quadVBO);
//    glBindVertexArray(quadVAO);
//    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(1);
//    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
//    glBindVertexArray(0);
//
//    // load textures
//    // -------------
//    unsigned int cubeTexture = loadTexture("../../image/container2.png");
//    unsigned int floorTexture = loadTexture("../../image/container.jpg");
//
//    // shader configuration
//    // --------------------
//    shader.use();
//    shader.setInt("texture1", 0);
//    screenshader.use();
//    screenshader.setInt("screenTexture", 0);
//
//    // ��������
//    unsigned int framebuffer;
//    glGenFramebuffers(1, &framebuffer);
//    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
//
//    // ����һ������ͼ�񣬽�����Ϊ��ɫ�������ӵ�֡������
//    unsigned int texColorBuffer;
//    glGenTextures(1, &texColorBuffer);
//    glBindTexture(GL_TEXTURE_2D, texColorBuffer);
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL); // �Ͷ�ȡ�����ļ����ƣ��������data����������NULL����ʾ���������ڴ��û�������
//                                                                                         // ��������Ⱦ��֡����֮���ٽ���
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    glBindTexture(GL_TEXTURE_2D, 0);
//    // ����������ӵ���ǰ�󶨵�֡������� // ����������Ŀ�꣬�����ļ����ͣ����ӵ��������ͣ��༶��Զ����ļ���
//    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColorBuffer, 0);
//    // ������ӵ�����Ⱥ�ģ�建������֡������� ����
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, 800, 600, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);
//    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texColorBuffer, 0);
//
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_STENCIL_INDEX, 800, 600, 0, GL_STENCIL_INDEX, GL_UNSIGNED_BYTE, NULL);
//    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_STENCIL_ATTACHMENT, GL_TEXTURE_2D, texColorBuffer, 0);
//
//    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, 800, 600, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
//    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, texColorBuffer, 0);
//
//    // ��Ⱦ���������Ⱦ�������ֱ�ӽ����е���Ⱦ���ݴ��浽���Ļ����У��������κ���������ʽ��ת����������Ϊһ������Ŀ�д������ʡ������ɶ�ȡ
//    /*
//        ��Ⱦ���������Ϊ���֡��������ṩһЩ�Ż�����֪��ʲôʱ��ʹ����Ⱦ�������ʲôʱ��ʹ�������Ǻ���Ҫ�ġ�
//        ͨ���Ĺ����ǣ�����㲻��Ҫ��һ�������в������ݣ���ô���������ʹ����Ⱦ�������������ǵ�ѡ��
//        �������Ҫ�ӻ����в�����ɫ�����ֵ�����ݣ���ô��Ӧ��ѡ��������
//    */
//    // ��������ֻϣ��������ɫ���壬�����������Ļ��壬���ǿ���Ϊ���Ǵ���һ����Ⱦ�������(����Ⱦ��������������������Ϊ���Ƶ���Ⱥ�ģ�����)
//    unsigned int rbo;
//    glGenRenderbuffers(1, &rbo);
//    glBindRenderbuffer(GL_RENDERBUFFER, rbo);
//    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 600);
//    glBindRenderbuffer(GL_RENDERBUFFER, 0);
//
//    // ���ǽ���Ⱦ������󸽼ӵ�֡�������Ⱥ�ģ�帽����
//    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
//
//    // ���֡�����Ƿ��������ģ�������Ǵ�ӡ������Ϣ
//    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
//        std::cout << "ERROR::FRAMEBUFFER::Framebuffer is not complete! " << std::endl;
//    glBindFramebuffer(GL_FRAMEBUFFER, 0);
//    /*
//        �������֡����������ˣ�����ֻ��Ҫ�����֡�����������Ⱦ��֡����Ļ����ж�����Ĭ�ϵ�֡�����С�
//        ֮�����Ⱦָ���Ӱ�쵱ǰ�󶨵�֡���塣���е���Ⱥ�ģ���������ӵ�ǰ�󶨵�֡�������Ⱥ�ģ�帽���У�����еĻ�����ȡ��
//        ������������Ȼ��壬��ô���е���Ȳ��Բ��������ٹ�������Ϊ��ǰ�󶨵�֡�����в�������Ȼ��塣
//    */
//
//    // render loop
//    // -----------
//    while (!glfwWindowShouldClose(window))
//    {
//        // per-frame time logic
//        // --------------------
//        float currentFrame = static_cast<float>(glfwGetTime());
//        deltaTime = currentFrame - lastFrame;
//        lastFrame = currentFrame;
//
//        // input
//        // -----
//        processInput(window);
//
//        // render
//        // ------
//        // 1�����µ�֡�����Ϊ�����֡���壬������һ����Ⱦ����
//        glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);
//        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//        glEnable(GL_DEPTH_TEST);
//
//        shader.use();
//        glm::mat4 model = glm::mat4(1.0f);
//        glm::mat4 view = camera.GetViewMatrix();
//        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//        shader.setMat4("view", view);
//        shader.setMat4("projection", projection);
//        // cubes
//        glBindVertexArray(cubeVAO);
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D, cubeTexture);
//        model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
//        shader.setMat4("model", model);
//        glDrawArrays(GL_TRIANGLES, 0, 36);
//        model = glm::mat4(1.0f);
//        model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
//        shader.setMat4("model", model);
//        glDrawArrays(GL_TRIANGLES, 0, 36);
//        // floor
//        glBindVertexArray(planeVAO);
//        glBindTexture(GL_TEXTURE_2D, floorTexture);
//        shader.setMat4("model", glm::mat4(1.0f));
//        glDrawArrays(GL_TRIANGLES, 0, 6);
//        glBindVertexArray(0);
//
//        /*
//            ���ԣ�Ҫ����Ƴ�����һ�������ϣ�������Ҫ��ȡ���µĲ��裺
//            1�����µ�֡�����Ϊ�����֡���壬������һ����Ⱦ����
//            2����Ĭ�ϵ�֡����
//            3������һ�����������Ļ���ı��Σ���֡�������ɫ������Ϊ��������
//        */
//        // 2��
//        glBindFramebuffer(GL_FRAMEBUFFER, 0); // ����Ĭ��
//        glClearColor(0.1f, 0.1f, 0.1f, 0.1f);
//        glClear(GL_COLOR_BUFFER_BIT); // ���ԭ�е���ɫ
//
//        screenshader.use();
//        glBindVertexArray(quadVAO);
//        glDisable(GL_DEPTH_TEST);
//        glBindTexture(GL_TEXTURE_2D, texColorBuffer);
//        glDrawArrays(GL_TRIANGLES, 0, 6);
//        // ��Ϊ����ִ�е���Ⱦ��һ��ƽ�棬���ԾͿ�����Ӧ��άͼ����ķ�����fragshader�н���һЩ�������˹ģ�����񻯵�
//
//        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
//        // -------------------------------------------------------------------------------
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//
//    // optional: de-allocate all resources once they've outlived their purpose:
//    // ------------------------------------------------------------------------
//    glDeleteVertexArrays(1, &cubeVAO);
//    glDeleteVertexArrays(1, &planeVAO);
//    glDeleteVertexArrays(1, &quadVAO);
//    glDeleteBuffers(1, &cubeVBO);
//    glDeleteBuffers(1, &planeVBO);
//    glDeleteBuffers(1, &quadVBO);
//    glDeleteRenderbuffers(1, &rbo);
//    glDeleteFramebuffers(1, &framebuffer);
//
//    glfwTerminate();
//    return 0;
//}
//
//// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
//// ---------------------------------------------------------------------------------------------------------
//void processInput(GLFWwindow* window)
//{
//    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//        glfwSetWindowShouldClose(window, true);
//
//    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
//        camera.ProcessKeyboard(FORWARD, deltaTime);
//    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
//        camera.ProcessKeyboard(BACKWARD, deltaTime);
//    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
//        camera.ProcessKeyboard(LEFT, deltaTime);
//    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
//        camera.ProcessKeyboard(RIGHT, deltaTime);
//}
//
//// glfw: whenever the window size changed (by OS or user resize) this callback function executes
//// ---------------------------------------------------------------------------------------------
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//    // make sure the viewport matches the new window dimensions; note that width and 
//    // height will be significantly larger than specified on retina displays.
//    glViewport(0, 0, width, height);
//}
//
//// glfw: whenever the mouse moves, this callback is called
//// -------------------------------------------------------
//void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
//{
//    float xpos = static_cast<float>(xposIn);
//    float ypos = static_cast<float>(yposIn);
//
//    if (firstMouse)
//    {
//        lastX = xpos;
//        lastY = ypos;
//        firstMouse = false;
//    }
//
//    float xoffset = xpos - lastX;
//    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
//
//    lastX = xpos;
//    lastY = ypos;
//
//    camera.ProcessMouseMovement(xoffset, yoffset);
//}
//
//// glfw: whenever the mouse scroll wheel scrolls, this callback is called
//// ----------------------------------------------------------------------
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
//{
//    camera.ProcessMouseScroll(static_cast<float>(yoffset));
//}
//
//// utility function for loading a 2D texture from file
//// ---------------------------------------------------
//unsigned int loadTexture(char const* path)
//{
//    unsigned int textureID;
//    glGenTextures(1, &textureID);
//
//    int width, height, nrComponents;
//    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
//    if (data)
//    {
//        GLenum format;
//        if (nrComponents == 1)
//            format = GL_RED;
//        else if (nrComponents == 3)
//            format = GL_RGB;
//        else if (nrComponents == 4)
//            format = GL_RGBA;
//
//        glBindTexture(GL_TEXTURE_2D, textureID);
//        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
//        glGenerateMipmap(GL_TEXTURE_2D);
//
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//
//        stbi_image_free(data);
//    }
//    else
//    {
//        std::cout << "Texture failed to load at path: " << path << std::endl;
//        stbi_image_free(data);
//    }
//
//    return textureID;
//}