//#include <glad/glad.h> // 要在glfw之前
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
//
//float rate = 0.2f;
//
//float screenWidth = 800, screenHeight = 600;
//
////但是实际情况下根据处理器的能力不同，有些人可能会比其他人每秒绘制更多帧，也就是以更高的频率调用processInput函数
//float deltaTime = 0.0f; // 当前帧与上一帧的时间差
//float lastFrame = 0.0f; // 上一帧的时间
//
////camera
//Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);
////Camera camera(glm::vec3(0.0f, 0.0f, 3.0f)); // 为什么错？
//float lastX = screenWidth / 2.0f, lastY = screenHeight / 2.0f;
//bool firstMouse = true;
//
//// light
//glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
//
//void framebuffer_size_callback(GLFWwindow* window, int width, int height)
//{
//    glViewport(0, 0, width, height);
//}// 我们可以对窗口注册一个回调函数(Callback Function)，它会在每次窗口大小被调整的时候被调用
//
//void processInput(GLFWwindow* window)
//{
//    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) // 按下esc
//        glfwSetWindowShouldClose(window, true); // 把WindowShouldClose属性设置为 true的方法关闭GLFW
//    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) // 按下"上"键
//    {
//        rate += 0.001f;
//        if (rate >= 1.0f)
//            rate = 0.0f;
//    }
//    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) // 按下"下"键
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
//    // 第一步是计算鼠标自上一帧的偏移量
//    float xoffset = xpos - lastX;
//    float yoffset = lastY - ypos; // 注意这里是相反的，因为y坐标是从底部往顶部依次增大的?(鼠标上移，ypos减小)
//
//    lastX = xpos;
//    lastY = ypos;
//
//    float sensitivity = 0.2f; // 灵敏度
//    xoffset *= sensitivity;
//    yoffset *= sensitivity;
//
//    camera.ProcessMouseMovement(xoffset, yoffset);
//}
//
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
//    // 视野(Field of View)或fov定义了我们可以看到场景中多大的范围。当视野变小时，场景投影出来的空间就会减小，产生放大(Zoom In)了的感觉
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
//    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 指定版本3.3，核心模式
//    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // for Mac OS
//
//    // 创建窗口对象
//    GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "LearnOpenGL", NULL, NULL);
//    if (window == NULL)
//    {
//        std::cout << "Failed to create GLFW window" << std::endl;
//        glfwTerminate();
//        return -1;
//    }
//    glfwMakeContextCurrent(window);
//    glfwSetCursorPosCallback(window, mouse_callback); // 在glfw中注册回调函数
//    glfwSetScrollCallback(window, scroll_callback);
//
//    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED); // 应该隐藏光标，并捕捉(Capture)它
//
//    // glad管理opengl函数指针，初始化glad
//    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//    {
//        std::cout << "Failed to initialize GLAD" << std::endl;
//        return -1;
//    }
//
//    glViewport(0, 0, screenWidth, screenHeight); //glViewport函数前两个参数控制窗口左下角的位置。第三个和第四个参数控制渲染窗口的宽度和高度（像素）。
//
//    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//
//    // !--- 顶定输入 ---！//
//
//    glEnable(GL_DEPTH_TEST); // 开启深度测试 // z-buffer
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
//
//    glm::vec3 cubePositions[] = {
//        glm::vec3(0.0f,  0.0f,  0.0f),
//        glm::vec3(2.0f,  5.0f, -15.0f),
//        glm::vec3(-1.5f, -2.2f, -2.5f),
//        glm::vec3(-3.8f, -2.0f, -12.3f),
//        glm::vec3(2.4f, -0.4f, -3.5f),
//        glm::vec3(-1.7f,  3.0f, -7.5f),
//        glm::vec3(1.3f, -2.0f, -2.5f),
//        glm::vec3(1.5f,  2.0f, -2.5f),
//        glm::vec3(1.5f,  0.2f, -1.5f),
//        glm::vec3(-1.3f,  1.0f, -1.5f)
//    };
//    // positions of the point lights
//    glm::vec3 pointLightPositions[] = {
//        glm::vec3(0.7f,  0.2f,  2.0f),
//        glm::vec3(2.3f, -3.3f, -4.0f),
//        glm::vec3(-4.0f,  2.0f, -12.0f),
//        glm::vec3(0.0f,  0.0f, -3.0f)
//    };
//
//    // point light color
//    glm::vec3 pointLightColors[] = {
//        glm::vec3(1.0f, 0.6f, 0.0f),
//        glm::vec3(1.0f, 0.0f, 0.0f),
//        glm::vec3(1.0f, 1.0f, 0.0f),
//        glm::vec3(0.2f, 0.2f, 1.0f)
//    };
//
//    // 1、 配置方块的VAO和VBO
//    unsigned int VBO, cubeVAO;
//    glGenVertexArrays(1, &cubeVAO);
//    glGenBuffers(1, &VBO);
//
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//    glBindVertexArray(cubeVAO);
//
//    // 顶点属性
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
//    glEnableVertexAttribArray(1);
//    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
//    glEnableVertexAttribArray(2);
//
//    // 2、 配置灯光的VAO（VBO保持不变;灯光对象的顶点相同，也是3D立方体）
//    unsigned int lightCubeVAO;
//    glGenVertexArrays(1, &lightCubeVAO);
//    glBindVertexArray(lightCubeVAO);
//
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(0);
//
//
//    Shader ourShader("./light_cube.vs", "./light_cube.fs");
//    Shader lightCubeShader("./light_light_cube.vs", "./light_light_cube.fs");
//
//    //glBindVertexArray(0);
//
//    glm::mat4 model; // 前面的trans实质上就是model矩阵，对模型进行变换
//
//    glm::mat4 view;
//    glm::mat4 projection;
//
//
//    // 载入纹理
//    unsigned int diffuseMap = loadTexture("../../image/container2.png");
//    unsigned int specularMap = loadTexture("../../image/container2_specular.png");
//    unsigned int emissionMap = loadTexture("../../image/matrix.jpg");
//
//    while (!glfwWindowShouldClose(window))
//    {
//        // 输入
//        processInput(window);
//
//        // 渲染指令
//        glClearColor(0.75f, 0.52f, 0.3f, 1.0f); // 除了glClear之外，我们还调用了glClearColor来设置清空屏幕所用的颜色。当调用glClear函数，清除颜色缓冲之后，整个颜色缓冲都会被填充为glClearColor里所设置的颜色。在这里，我们将屏幕设置为了类似黑板的深蓝绿色。
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 可能的缓冲位有GL_COLOR_BUFFER_BIT，GL_DEPTH_BUFFER_BIT和GL_STENCIL_BUFFER_BIT
//
//        // per-frame time logic
//        float currentFrame = glfwGetTime();
//        deltaTime = currentFrame - lastFrame;
//        lastFrame = currentFrame;
//
//        glm::vec3 lightColor = glm::vec3(1.0f);
//        // !--- 绘制图形  ---！//
//        ourShader.use();
//        ourShader.setVec3("viewPos", camera.Position);
//        ourShader.setFloat("material.shininess", 32.0f);
//        ourShader.setInt("material.diffuse", 0);
//        ourShader.setInt("material.specular", 1);
//
//        /*
//           Here we set all the uniforms for the 5/6 types of lights we have. We have to set them manually and index
//           the proper PointLight struct in the array to set each uniform variable. This can be done more code-friendly
//           by defining light types as classes and set their values in there, or by using a more efficient uniform approach
//           by using 'Uniform buffer objects', but that is something we'll discuss in the 'Advanced GLSL' tutorial.
//        */
//        // directional light
//        ourShader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);
//        ourShader.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
//        ourShader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
//        ourShader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);
//        // point light 1
//        ourShader.setVec3("pointLights[0].position", pointLightPositions[0]);
//        ourShader.setVec3("pointLights[0].ambient", 0.1f * pointLightColors[0]); // /*scene0*/: ourShader.setVec3("pointLights[0].ambient", 0.05f, 0.05f, 0.05f);
//        ourShader.setVec3("pointLights[0].diffuse", 0.8f * pointLightColors[0]); // /*scene0*/: ourShader.setVec3("pointLights[0].diffuse", 0.8f, 0.8f, 0.8f);
//        ourShader.setVec3("pointLights[0].specular", pointLightColors[0]); // /*scene0*/: ourShader.setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
//        ourShader.setFloat("pointLights[0].constant", 1.0f);
//        ourShader.setFloat("pointLights[0].linear", 0.09f);
//        ourShader.setFloat("pointLights[0].quadratic", 0.032f);
//        // point light 2
//        ourShader.setVec3("pointLights[1].position", pointLightPositions[1]);
//        ourShader.setVec3("pointLights[1].ambient", 0.1f * pointLightColors[1]); // /*scene0*/: ourShader.setVec3("pointLights[1].ambient", 0.05f, 0.05f, 0.05f);
//        ourShader.setVec3("pointLights[1].diffuse", 0.8f * pointLightColors[1]); // /*scene0*/: ourShader.setVec3("pointLights[1].diffuse", 0.8f, 0.8f, 0.8f);
//        ourShader.setVec3("pointLights[1].specular", pointLightColors[1]);       // /*scene0*/: ourShader.setVec3("pointLights[1].specular", 1.0f, 1.0f, 1.0f);
//        ourShader.setFloat("pointLights[1].constant", 1.0f);
//        ourShader.setFloat("pointLights[1].linear", 0.09f);
//        ourShader.setFloat("pointLights[1].quadratic", 0.032f);
//        // point light 3
//        ourShader.setVec3("pointLights[2].position", pointLightPositions[2]);
//        ourShader.setVec3("pointLights[2].ambient", 0.1f * pointLightColors[2]); // /*scene0*/:ourShader.setVec3("pointLights[2].ambient", 0.05f, 0.05f, 0.05f);
//        ourShader.setVec3("pointLights[2].diffuse", 0.8f * pointLightColors[2]); // /*scene0*/:ourShader.setVec3("pointLights[2].diffuse", 0.8f, 0.8f, 0.8f);
//        ourShader.setVec3("pointLights[2].specular", pointLightColors[2]);       // /*scene0*/:ourShader.setVec3("pointLights[2].specular", 1.0f, 1.0f, 1.0f);
//        ourShader.setFloat("pointLights[2].constant", 1.0f);
//        ourShader.setFloat("pointLights[2].linear", 0.09f);
//        ourShader.setFloat("pointLights[2].quadratic", 0.032f);
//        // point light 4
//        ourShader.setVec3("pointLights[3].position", pointLightPositions[3]);
//        ourShader.setVec3("pointLights[3].ambient", 0.1f * pointLightColors[3]); // /*scene0*/:ourShader.setVec3("pointLights[3].ambient", 0.05f, 0.05f, 0.05f);
//        ourShader.setVec3("pointLights[3].diffuse", 0.8f * pointLightColors[3]); // /*scene0*/:ourShader.setVec3("pointLights[3].diffuse", 0.8f, 0.8f, 0.8f);
//        ourShader.setVec3("pointLights[3].specular", pointLightColors[3]);       // /*scene0*/:ourShader.setVec3("pointLights[3].specular", 1.0f, 1.0f, 1.0f);
//        ourShader.setFloat("pointLights[3].constant", 1.0f);
//        ourShader.setFloat("pointLights[3].linear", 0.09f);
//        ourShader.setFloat("pointLights[3].quadratic", 0.032f);
//        // spotLight
//        ourShader.setVec3("spotLight.position", camera.Position);
//        ourShader.setVec3("spotLight.direction", camera.Front);
//        ourShader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
//        ourShader.setVec3("spotLight.diffuse", 1.0f, 1.0f, 1.0f);
//        ourShader.setVec3("spotLight.specular", 1.0f, 1.0f, 1.0f);
//        ourShader.setFloat("spotLight.constant", 1.0f);
//        ourShader.setFloat("spotLight.linear", 0.09f);
//        ourShader.setFloat("spotLight.quadratic", 0.032f);
//        ourShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
//        ourShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));
//       
//        projection = glm::perspective(glm::radians(camera.Zoom), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
//        view = camera.GetViewMatrix();
//        model = glm::mat4(1.0f);
//
//        //glm::mat4 clip_space = projection * view * model;
//        //glUniformMatrix4fv(glGetUniformLocation(ourShader.ID, "clip_space"), 1, GL_FALSE, &clip_space[0][0]);
//        //ourShader.setMat4("model", model);
//        ourShader.setMat4("view", view);
//        ourShader.setMat4("projection", projection);
//
//        // 激活纹理，绑定纹理
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D, diffuseMap);
//        glActiveTexture(GL_TEXTURE1);
//        glBindTexture(GL_TEXTURE_2D, specularMap);
//        glActiveTexture(GL_TEXTURE2);
//        glBindTexture(GL_TEXTURE_2D, emissionMap);
//
//        // 实际渲染物体
//        glBindVertexArray(cubeVAO);
//        //glDrawArrays(GL_TRIANGLES, 0, 36); 
//        for (int i = 0; i < 10; i++) {
//            glm::mat4 model = glm::mat4(1.0f); // 循环前初始化
//            model = glm::translate(model, cubePositions[i]);
//            float angle = 20.0f * i;
//            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
//            ourShader.setMat4("model", model);
//            glDrawArrays(GL_TRIANGLES, 0, 36);
//        }
//
//        
//        // 光源 //
//            // 光源绕圈
//        //float radius = pow((lightPos.x * lightPos.x + lightPos.y * lightPos.y),0.5);
//        //lightPos.x = sin(currentFrame) * radius;
//        //lightPos.y = cos(currentFrame) * radius;
//
//        lightCubeShader.use();
//        lightCubeShader.setMat4("view", view);
//        lightCubeShader.setMat4("projection", projection);
//        // 实际渲染灯光
//        glBindVertexArray(lightCubeVAO);
//        for (int i = 0; i < 4; i++) {
//            lightCubeShader.setVec3("lightColor", pointLightColors[i]);
//            glm::mat4 model = glm::mat4(1.0f); // 循环前初始化
//            model = glm::translate(model, pointLightPositions[i]);
//            model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
//            lightCubeShader.setMat4("model", model);
//            glDrawArrays(GL_TRIANGLES, 0, 36);
//        }
//       
//        // 检查并调用事件，交换缓冲
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//
//    // optional: de-allocate all resources once they've outlived their purpose:
//    // ------------------------------------------------------------------------
//    glDeleteVertexArrays(1, &cubeVAO);
//    glDeleteVertexArrays(1, &lightCubeVAO);
//    glDeleteBuffers(1, &VBO);
//    ourShader.deleteprogram();
//
//    glfwTerminate(); // 释放之前分配的资源
//
//    return 0;
//}
//
///*
//    // 物体 //
//        ourShader.use();        
//        //ourShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
//        //ourShader.setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
//        ourShader.setInt("material.diffuse", 0); // 相当与是把纯色的漫反射替换为纹理中黑色代表颜色向量vec3(0.0)（无高光），灰色代表颜色向量vec3(0.5)（少高光）
//        //ourShader.setVec3("material.specular", 0.5f, 0.5f, 0.5f);
//        ourShader.setInt("material.specular", 1); // 相当是对specularMap图片进行采样，纹理中
//        // ourShader.setVec3("light.position", lightPos); // 统一参数必须要在shader工程启用之后
//        // ourShader.setVec3("light.direction", -0.2f, -1.0f, -0.3f);
//        ourShader.setVec3("light.position", camera.Position); // 作为聚光的要素
//        ourShader.setVec3("light.direction", camera.Front);
//        ourShader.setFloat("light.cutOff", glm::cos(glm::radians(12.5f))); // 用角度值计算了一个余弦值，方便传入FragShader比较
//        ourShader.setFloat("light.outerCutOff", glm::cos(glm::radians(17.5f)));
//        ourShader.setVec3("viewPos", camera.Position);
//
//        ourShader.setVec3("light.ambient", 0.1f, 0.1f, 0.1f);
//        ourShader.setVec3("light.diffuse", 0.8f, 0.8f, 0.8f);
//        ourShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
//
//        ourShader.setFloat("light.constant", 1.0f);
//        ourShader.setFloat("light.linear", 0.09f);
//        ourShader.setFloat("light.quadratic", 0.032f);
//
//        ourShader.setFloat("material.shininess", 32.0f); // 结构体只是充当uniform变量们的一个命名空间。所以如果想填充这个结构体的话，我们必须设置每个单独的uniform，但要以结构体名为前缀：
//        //ourShader.setInt("material.emission", 2);
//
//        //glm::vec3 lightColor = glm::vec3(1.0f);
//
//        //glm::vec3 diffuseColor = 0.8f * lightColor;
//        //glm::vec3 ambientColor = 0.1f * diffuseColor;
//*/