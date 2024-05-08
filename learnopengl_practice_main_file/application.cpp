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
//    float currentFrame = glfwGetTime();
//    deltaTime = currentFrame - lastFrame;
//    lastFrame = currentFrame;
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
//
//    //// 接下来我们把偏移量加到全局变量pitch和yaw上
//    //yaw += xoffset;
//    //pitch += yoffset;
//
//    //// 第三步，我们需要给摄像机添加一些限制
//    //if (pitch > 89.0f)
//    //    pitch = 89.0f;
//    //if (pitch < -89.0f)
//    //    pitch = -89.0f;
//
//    //// 第四也是最后一步，就是通过俯仰角和偏航角来计算以得到真正的方向向量
//    //glm::vec3 front;
//    //front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
//    //front.y = sin(glm::radians(pitch));
//    //front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
//    //cameraFront = glm::normalize(front);
//}
//
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
//    //if (fov >= 1.0f && fov <= 45.0f)
//    //    fov -= yoffset; // 当滚动鼠标滚轮的时候，yoffset值代表我们竖直滚动的大小
//    //if (fov <= 1.0f)
//    //    fov = 1.0f;
//    //if (fov >= 45.0f)
//    //    fov = 45.0f;
//    camera.ProcessMouseScroll(yoffset);
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
//    //float vertices[] = {
//    //// 位置             //颜色            //纹理坐标
//    // 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // 右上角
//    // 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // 右下角
//    //-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // 左下角
//    //-0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // 左上角
//    //};
//
//    glEnable(GL_DEPTH_TEST); // 开启深度测试 // z-buffer
//
//    float vertices[] = {
//        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
//         0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
//         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
//
//        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//         0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
//        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
//        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//
//        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//
//         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//         0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//         0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//
//        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//         0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
//         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//         0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
//        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
//        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
//
//        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
//         0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
//         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//         0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
//        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
//        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
//    };
//
//    unsigned int indices[] = {
//        // 注意索引从0开始! 
//        // 此例的索引(0,1,2,3)就是顶点数组vertices的下标，
//        // 这样可以由下标代表顶点组合成矩形
//        0, 1, 3, // 第一个三角形
//        1, 2, 3  // 第二个三角形
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
//
//    //创建vertex array
//    unsigned int VAO;
//    glGenVertexArrays(1, &VAO);
//    // 1. 绑定顶点数组对象 // 首先绑定顶点数组对象，然后绑定和设置顶点缓冲区，然后配置顶点属性。
//    glBindVertexArray(VAO);
//
//    // !--- 元素缓冲对象 ---！//
//    //unsigned int EBO;
//    //glGenBuffers(1, &EBO); /* 3D时做的更改 */
//
//    //创建vertex buffer
//    unsigned int VBO;
//    glGenBuffers(1, &VBO);
//    // 2. 把我们的顶点数组复制到一个顶点缓冲中，供OpenGL使用
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//    // 现在我们已经把顶点数据储存在显卡的内存中，用VBO这个顶点缓冲对象管理
//
//    // 3. 复制我们的索引数组到一个索引缓冲中，供OpenGL使用
//    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); /* 3D时做的更改 */
//
//    // !--- 链接顶点属性 ---！//
//    // 具体是从哪个VBO（程序中可以有多个VBO）获取则是通过在调用glVertexAttribPointer时绑定到GL_ARRAY_BUFFER的VBO决定的。
//    // 由于在调用glVertexAttribPointer之前绑定的是先前定义的VBO对象，顶点属性0现在会链接到它的顶点数据。
//    // 属性编号（Location），属性大小, 数据类型，是否标准化，步长（一个顶点属性的总长度），偏移（相对于开头）
//    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
//    //glEnableVertexAttribArray(0); // 以顶点属性位置值作为参数，启用顶点属性；顶点属性默认是禁用的。
//    //// 添加顶点颜色的顶点属性
//    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
//    //glEnableVertexAttribArray(1);
//    ////纹理坐标属性
//    //glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
//    //glEnableVertexAttribArray(2);  /* 3D时做的更改 */
//
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(0); 
//    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
//    glEnableVertexAttribArray(2);
//
//
//    // !--- 顶点着色器 ---！//
//    // 着色器语言GLSL(OpenGL Shading Language)编写顶点着色器
//
//    // !--- 片段着色器 ---！//
//    // !--- 着色器程序 ---！// 把两个着色器对象链接到一个用来渲染的着色器程序(Shader Program)中
//
//    Shader ourShader("./shader.vs", "./shader.fs");
//
//
//    // 得到的结果就是一个程序对象，我们可以调用glUseProgram函数，用刚创建的程序对象作为它的参数，以激活这个程序对象：
//    // 在glUseProgram函数调用之后，每个着色器调用和渲染调用都会使用这个程序对象（也就是之前写的着色器)了
//    // 把着色器对象链接到程序对象以后，记得删除着色器对象，我们不再需要它们
//
//    //glBindVertexArray(0);
//
//    // !--- 加载与创建纹理 ---！//
//    //生成纹理
//    unsigned int texture;
//    glGenTextures(1, &texture);
//    glBindTexture(GL_TEXTURE_2D, texture);
//    //为当前绑定的纹理对象设置环绕，过滤方式
//    /*
//        纹理坐标超出默认范围时，每个选项都有不同的视觉效果输出, s, t, r -> x, y, z
//        当进行放大(Magnify)和缩小(Minify)操作的时候可以设置纹理过滤的选项
//    */
//    //float borderColor[] = { 1.0f, 0.0f, 0.0f, 1.0f };
//    //glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    //加载并生成纹理
//    int width, height, nrChannels;
//    stbi_set_flip_vertically_on_load(true);//加载图片时，竖直翻转
//    unsigned char* data = stbi_load("../../image/container.jpg", &width, &height, &nrChannels, 0);
//    if (data) {
//        /*
//            当前绑定的纹理对象就会被附加上纹理图像。然而，目前只有基本级别(Base-level)的纹理图像被加载了，如果要使用多级渐远纹理
//            直接在生成纹理之后调用glGenerateMipmap。这会为当前绑定的纹理自动生成所有需要的多级渐远纹理。
//        */
//        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//        glGenerateMipmap(GL_TEXTURE_2D);
//    }
//    else {
//        std::cout << "Failed to load texture" << std::endl;
//    }
//    //释放图像的内存是一个很好的习惯
//    stbi_image_free(data);
//
//    // 第二个纹理
//    unsigned int texture2;
//    glGenTextures(1, &texture2);
//    glBindTexture(GL_TEXTURE_2D, texture2);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    //加载并生成纹理
//    data = stbi_load("../../image/awesomeface.png", &width, &height, &nrChannels, 0);
//    if (data) {
//        /*
//            当前绑定的纹理对象就会被附加上纹理图像。然而，目前只有基本级别(Base-level)的纹理图像被加载了，如果要使用多级渐远纹理
//            直接在生成纹理之后调用glGenerateMipmap。这会为当前绑定的纹理自动生成所有需要的多级渐远纹理。
//        */
//        // 这个图像有透明度信息，用RGBA
//        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
//        glGenerateMipmap(GL_TEXTURE_2D);
//    }
//    else {
//        std::cout << "Failed to load texture" << std::endl;
//    }
//    //释放图像的内存是一个很好的习惯
//    stbi_image_free(data);
//
//    ourShader.use(); // 不要忘记在设置uniform变量之前激活着色器程序！
//    glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0); // 手动设置
//    ourShader.setInt("texture2", 1); // 或者使用着色器类设置
//
//    //glm::mat4 trans;
//    //trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f)); // 沿z轴旋转90度，radians(90.0f)转弧度，
//    //trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f)); // 每个轴都缩放到0.5倍
//    //// GLM会自动将矩阵相乘，返回的结果是一个包括了多个变换的变换矩阵
//
//    ////第一个是uniform的位置值。第二个参数告诉OpenGL我们将要发送多少个矩阵。第三个参数询问我们是否希望对我们的矩阵进行转置(Transpose)。
//    //// 最后一个参数是真正的矩阵数据，但是GLM并不是把它们的矩阵储存为OpenGL所希望接受的那种，因此我们要先用GLM的自带的函数value_ptr来变换这些数据。
//    //glUniformMatrix4fv(glGetUniformLocation(ourShader.ID, "transform"), 1, GL_FALSE, glm::value_ptr(trans));
//
//    glm::mat4 model; // 前面的trans实质上就是model矩阵，对模型进行变换
// 
//    glm::mat4 view;
//    //view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
//    //定义lookat矩阵：定义一个摄像机位置，一个目标位置和一个相机坐标的向上分量
//    //view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
//    //                   glm::vec3(0.0f, 0.0f, 0.0f),
//    //                   glm::vec3(0.0f, 1.0f, 0.0f));
//
//    glm::mat4 projection;
//
//    while (!glfwWindowShouldClose(window))
//    {
//        // 输入
//        processInput(window);
//
//        // 渲染指令
//        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // 除了glClear之外，我们还调用了glClearColor来设置清空屏幕所用的颜色。当调用glClear函数，清除颜色缓冲之后，整个颜色缓冲都会被填充为glClearColor里所设置的颜色。在这里，我们将屏幕设置为了类似黑板的深蓝绿色。
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 可能的缓冲位有GL_COLOR_BUFFER_BIT，GL_DEPTH_BUFFER_BIT和GL_STENCIL_BUFFER_BIT
//
//        // !--- 绘制图形  ---！//
//
//        // 利用uniform需要在gluseprogram()之后
//        // 更新uniform颜色 
//        //float timeValue = glfwGetTime();
//        //float greenValue = sin(timeValue) / 2.0f + 0.5f;
//        //int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
//        //glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
//
//        //// 随时间旋转
//        //glm::mat4 trans; // 这里实际对物体时是先旋转，再位移（因为这里相对于右乘trans矩阵，先的矩阵在最终tranform的左边）
//        //trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
//        //trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
//        //glUniformMatrix4fv(glGetUniformLocation(ourShader.ID, "transform"), 1, GL_FALSE, glm::value_ptr(trans));
//
//        //model = glm::rotate(model, (float)glfwGetTime() * 0.0002f, glm::vec3(0.5f, 1.0f, 0.0f));
//        glm::mat4 clip_space;
//        //glUniformMatrix4fv(glGetUniformLocation(ourShader.ID, "clip_space"), 1, GL_FALSE, &clip_space[0][0]);
//
//
//        // 绑定纹理 // 先绑定两个纹理到对应的纹理单元，然后定义哪个uniform采样器对应哪个纹理单元：
//        glActiveTexture(GL_TEXTURE0);  // 默认激活的
//        glBindTexture(GL_TEXTURE_2D, texture);
//        glActiveTexture(GL_TEXTURE1);
//        glBindTexture(GL_TEXTURE_2D, texture2);
//
//        ourShader.setFloat("rate", rate);
//
//        // 绘制a
//        glBindVertexArray(VAO);
//        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//        //glDrawArrays(GL_TRIANGLES, 0, 36);
//
//          //相机绕圈转动的view
//        //float radius = 10.0f;
//        //float camX = sin(glfwGetTime()) * radius;
//        //float camZ = cos(glfwGetTime()) * radius;
//        //view = glm::lookAt(glm::vec3(camX, 0.0f, camZ),
//        //    glm::vec3(0.0f, 0.0f, 0.0f),
//        //    glm::vec3(0.0f, 1.0f, 0.0f));
//
//        //view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);//cameraFront是目视方向，指标是方向，大小无所谓
//        view = camera.GetViewMatrix();
//        projection = glm::perspective(glm::radians(camera.Zoom), (float)(screenWidth / screenHeight), 0.1f, 100.0f);
//        // 视野(Field of View)或fov定义了我们可以看到场景中多大的范围。当视野变小时，场景投影出来的空间就会减小，产生放大(Zoom In)了的感觉
//
//
//        for (int i = 0; i < 10; i++) {
//            model = glm::mat4(1.0f);
//            model = glm::translate(model, cubePositions[i]);
//            if (i != 0)model = glm::rotate(model, (float)glfwGetTime() * (float)i, cubePositions[i]);
//            clip_space = projection * view * model;
//            glUniformMatrix4fv(glGetUniformLocation(ourShader.ID, "clip_space"), 1, GL_FALSE, &clip_space[0][0]);
//            glDrawArrays(GL_TRIANGLES, 0, 36);
//        }
//
//
//        //// 第二个绘制 随时间缩放
//        //trans = glm::mat4(1.0f);
//        //trans = glm::translate(trans, glm::vec3(-0.5f, 0.5f, 0.0f));
//        //float scalerate = sin(glfwGetTime()) >= 0 ? sin(glfwGetTime()) : -sin(glfwGetTime());
//        //trans = glm::scale(trans, glm::vec3(scalerate, scalerate, scalerate));
//        //glUniformMatrix4fv(glGetUniformLocation(ourShader.ID, "transform"), 1, GL_FALSE, glm::value_ptr(trans));
//        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//
//        // 检查并调用事件，交换缓冲
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//
//    // optional: de-allocate all resources once they've outlived their purpose:
//    // ------------------------------------------------------------------------
//    glDeleteVertexArrays(1, &VAO);
//    glDeleteBuffers(1, &VBO);
//    ourShader.deleteprogram();
//
//    glfwTerminate(); // 释放之前分配的资源
//
//    return 0;
//}