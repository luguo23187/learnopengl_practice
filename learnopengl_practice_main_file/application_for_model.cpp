//#include <glad/glad.h> // Ҫ��glfw֮ǰ
//#include <glfw/glfw3.h> 
//#include <iostream>
//
//#include <glm/glm.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtc/type_ptr.hpp>
//
//#include "shader_s.h"
//#include "stb_image.h"
//#include "camera.h"
//#include "Model.h"
//
//float rate = 0.2f;
//
//float screenWidth = 800, screenHeight = 600;
//
////����ʵ������¸��ݴ�������������ͬ����Щ�˿��ܻ��������ÿ����Ƹ���֡��Ҳ�����Ը��ߵ�Ƶ�ʵ���processInput����
//float deltaTime = 0.0f; // ��ǰ֡����һ֡��ʱ���
//float lastFrame = 0.0f; // ��һ֡��ʱ��
//
////camera
//Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);
////Camera camera(glm::vec3(0.0f, 0.0f, 3.0f)); // Ϊʲô��
//float lastX = screenWidth / 2.0f, lastY = screenHeight / 2.0f;
//bool firstMouse = true;
//
//// light
//glm::vec3 lightPos(1.2f, 2.0f, 1.2f);
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//    glViewport(0, 0, width, height);
//}// ���ǿ��ԶԴ���ע��һ���ص�����(Callback Function)��������ÿ�δ��ڴ�С��������ʱ�򱻵���
//
//void processInput(GLFWwindow* window)
//{
//    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) // ����esc
//        glfwSetWindowShouldClose(window, true); // ��WindowShouldClose��������Ϊ true�ķ����ر�GLFW
//    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) // ����"��"��
//    {
//        rate += 0.001f;
//        if (rate >= 1.0f)
//            rate = 0.0f;
//    }
//    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) // ����"��"��
//    {
//        rate -= 0.001f;
//        if (rate <= 0.0f)
//            rate = 1.0f;
//    }
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
//void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
//    if (firstMouse) {
//        lastX = xpos;
//        lastY = ypos;
//        firstMouse = false;
//    }
//
//    // ��һ���Ǽ����������һ֡��ƫ����
//    float xoffset = xpos - lastX;
//    float yoffset = lastY - ypos; // ע���������෴�ģ���Ϊy�����Ǵӵײ����������������?(������ƣ�ypos��С)
//
//    lastX = xpos;
//    lastY = ypos;
//
//    float sensitivity = 0.2f; // ������
//    xoffset *= sensitivity;
//    yoffset *= sensitivity;
//
//    camera.ProcessMouseMovement(xoffset, yoffset);
//}
//
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
//    // ��Ұ(Field of View)��fov���������ǿ��Կ��������ж��ķ�Χ������Ұ��Сʱ������ͶӰ�����Ŀռ�ͻ��С�������Ŵ�(Zoom In)�˵ĸо�
//    camera.ProcessMouseScroll(yoffset);
//}
//
//unsigned int loadTexture(char const* path) {
//    unsigned int textureID;
//    glGenTextures(1, &textureID);
//
//    int width, height, nrComponents;
//    stbi_set_flip_vertically_on_load(true);
//    unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
//    if (data) {
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
//
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    }
//    else {
//        std::cout << "Failed to load texture from path: " << path << std::endl;
//    }
//    stbi_image_free(data);
//
//    return textureID;
//}
//
//int main()
//{
//    glfwInit();
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // ָ���汾3.3������ģʽ
//    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // for Mac OS
//
//    // �������ڶ���
//    GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "LearnOpenGL", NULL, NULL);
//    if (window == NULL)
//    {
//        std::cout << "Failed to create GLFW window" << std::endl;
//        glfwTerminate();
//        return -1;
//    }
//    glfwMakeContextCurrent(window);
//    glfwSetCursorPosCallback(window, mouse_callback); // ��glfw��ע��ص�����
//    glfwSetScrollCallback(window, scroll_callback);
//
//    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // Ӧ�����ع�꣬����׽(Capture)��
//
//    // glad����opengl����ָ�룬��ʼ��glad
//    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//    {
//        std::cout << "Failed to initialize GLAD" << std::endl;
//        return -1;
//    }
//
//    glViewport(0, 0, screenWidth, screenHeight); //glViewport����ǰ�����������ƴ������½ǵ�λ�á��������͵��ĸ�����������Ⱦ���ڵĿ�Ⱥ͸߶ȣ����أ���
//
//    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//
//    // !--- �������� ---��//
//
//    glEnable(GL_DEPTH_TEST); // ������Ȳ��� // z-buffer
//
//    float vertices[] = {
//        // positions          // normals           // texture coords
//        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
//         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 0.0f,
//         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
//         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f, 1.0f,
//        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 1.0f,
//        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f, 0.0f,
//
//        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
//         0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 0.0f,
//         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
//         0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   1.0f, 1.0f,
//        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 1.0f,
//        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,   0.0f, 0.0f,
//
//        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
//        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
//        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
//        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
//        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
//        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
//
//         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
//         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f,
//         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
//         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 1.0f,
//         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f, 0.0f,
//         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f,
//
//        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
//         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 1.0f,
//         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
//         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f, 0.0f,
//        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 0.0f,
//        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f, 1.0f,
//
//        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f,
//         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 1.0f,
//         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
//         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f, 0.0f,
//        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 0.0f,
//        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f, 1.0f
//    };
//    unsigned int VBO;
//    unsigned int lightCubeVAO;
//    glGenBuffers(1, &VBO);
//    glGenVertexArrays(1, &lightCubeVAO);
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//    glBindVertexArray(lightCubeVAO);
//    
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(0);
//
//    // build ans compile shaders
//    Shader ourShader("./model_loading.vs", "./model_loading.fs");
//    Shader lightShader("./light_light_cube.vs", "./light_light_cube.fs");
//
//    // load models
//    Model ourModel("../../sample_model/nanosuit/nanosuit.obj");
//
//    //glBindVertexArray(0);
//
//    glm::mat4 model; // ǰ���transʵ���Ͼ���model���󣬶�ģ�ͽ��б任
//    glm::mat4 view;
//    glm::mat4 projection;
//    glm::vec3 lightColor = glm::vec3(1.0f);
//
//    while (!glfwWindowShouldClose(window))
//    {
//        // ����
//        processInput(window);
//
//        // ��Ⱦָ��
//        glClearColor(0.75f, 0.52f, 0.3f, 1.0f); // ����glClear֮�⣬���ǻ�������glClearColor�����������Ļ���õ���ɫ��������glClear�����������ɫ����֮��������ɫ���嶼�ᱻ���ΪglClearColor�������õ���ɫ����������ǽ���Ļ����Ϊ�����ƺڰ��������ɫ��
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // ���ܵĻ���λ��GL_COLOR_BUFFER_BIT��GL_DEPTH_BUFFER_BIT��GL_STENCIL_BUFFER_BIT
//
//        // per-frame time logic
//        float currentFrame = glfwGetTime();
//        deltaTime = currentFrame - lastFrame;
//        lastFrame = currentFrame;
//
//        float radius = pow((lightPos.x * lightPos.x + lightPos.z * lightPos.z), 0.5);
//        lightPos.x = sin(currentFrame) * radius;
//        lightPos.z = cos(currentFrame) * radius;
//
//        ourShader.use();
//        ourShader.setFloat("material.shininess", 32.0f);
//        ourShader.setVec3("pointLight.position", lightPos);
//        ourShader.setVec3("pointLight.ambient", 0.3f * lightColor);
//        ourShader.setVec3("pointLight.diffuse", 0.8f * lightColor);
//        ourShader.setVec3("pointLight.specular", lightColor);
//        ourShader.setFloat("pointLight.constant", 1.0f);
//        ourShader.setFloat("pointLight.linear", 0.09f);
//        ourShader.setFloat("pointLight.quadratic", 0.032f);
//        ourShader.setVec3("viewPos", camera.Position);
//
//        projection = glm::perspective(glm::radians(camera.Zoom), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
//        view = camera.GetViewMatrix();
//        ourShader.setMat4("projection", projection);
//        ourShader.setMat4("view", view);
//
//        // render the loaded model
//        model = glm::mat4(1.0f);
//        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));
//        model = glm::scale(model, glm::vec3(0.25f, 0.25f, 0.25f));
//        ourShader.setMat4("model", model);
//        ourModel.Draw(ourShader);
//
//        // -- light shader -- //
//        
//        lightShader.use();
//        lightShader.setMat4("view", view);
//        lightShader.setMat4("projection", projection);
//        lightShader.setVec3("lightColor", lightColor);
//        glBindVertexArray(lightCubeVAO);
//        model = glm::mat4(1.0f);
//        model = glm::translate(model, lightPos);
//        model = glm::scale(model, glm::vec3(0.2f));
//        lightShader.setMat4("model", model);
//        glDrawArrays(GL_TRIANGLES, 0, 36);
//        // -- light shader -- //
//
//        // ��鲢�����¼�����������
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//
//    // optional: de-allocate all resources once they've outlived their purpose:
//    // ------------------------------------------------------------------------
//    ourShader.deleteprogram();
//
//    glfwTerminate(); // �ͷ�֮ǰ�������Դ
//
//    return 0;
//}