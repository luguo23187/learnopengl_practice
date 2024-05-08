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
//
//    //// ���������ǰ�ƫ�����ӵ�ȫ�ֱ���pitch��yaw��
//    //yaw += xoffset;
//    //pitch += yoffset;
//
//    //// ��������������Ҫ����������һЩ����
//    //if (pitch > 89.0f)
//    //    pitch = 89.0f;
//    //if (pitch < -89.0f)
//    //    pitch = -89.0f;
//
//    //// ����Ҳ�����һ��������ͨ�������Ǻ�ƫ�����������Եõ������ķ�������
//    //glm::vec3 front;
//    //front.x = cos(glm::radians(pitch)) * cos(glm::radians(yaw));
//    //front.y = sin(glm::radians(pitch));
//    //front.z = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
//    //cameraFront = glm::normalize(front);
//}
//
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
//    //if (fov >= 1.0f && fov <= 45.0f)
//    //    fov -= yoffset; // �����������ֵ�ʱ��yoffsetֵ����������ֱ�����Ĵ�С
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
//    //float vertices[] = {
//    //// λ��             //��ɫ            //��������
//    // 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // ���Ͻ�
//    // 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // ���½�
//    //-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // ���½�
//    //-0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // ���Ͻ�
//    //};
//
//    glEnable(GL_DEPTH_TEST); // ������Ȳ��� // z-buffer
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
//        // ע��������0��ʼ! 
//        // ����������(0,1,2,3)���Ƕ�������vertices���±꣬
//        // �����������±��������ϳɾ���
//        0, 1, 3, // ��һ��������
//        1, 2, 3  // �ڶ���������
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
//    //����vertex array
//    unsigned int VAO;
//    glGenVertexArrays(1, &VAO);
//    // 1. �󶨶���������� // ���Ȱ󶨶����������Ȼ��󶨺����ö��㻺������Ȼ�����ö������ԡ�
//    glBindVertexArray(VAO);
//
//    // !--- Ԫ�ػ������ ---��//
//    //unsigned int EBO;
//    //glGenBuffers(1, &EBO); /* 3Dʱ���ĸ��� */
//
//    //����vertex buffer
//    unsigned int VBO;
//    glGenBuffers(1, &VBO);
//    // 2. �����ǵĶ������鸴�Ƶ�һ�����㻺���У���OpenGLʹ��
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//    // ���������Ѿ��Ѷ������ݴ������Կ����ڴ��У���VBO������㻺��������
//
//    // 3. �������ǵ��������鵽һ�����������У���OpenGLʹ��
//    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW); /* 3Dʱ���ĸ��� */
//
//    // !--- ���Ӷ������� ---��//
//    // �����Ǵ��ĸ�VBO�������п����ж��VBO����ȡ����ͨ���ڵ���glVertexAttribPointerʱ�󶨵�GL_ARRAY_BUFFER��VBO�����ġ�
//    // �����ڵ���glVertexAttribPointer֮ǰ�󶨵�����ǰ�����VBO���󣬶�������0���ڻ����ӵ����Ķ������ݡ�
//    // ���Ա�ţ�Location�������Դ�С, �������ͣ��Ƿ��׼����������һ���������Ե��ܳ��ȣ���ƫ�ƣ�����ڿ�ͷ��
//    //glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
//    //glEnableVertexAttribArray(0); // �Զ�������λ��ֵ��Ϊ���������ö������ԣ���������Ĭ���ǽ��õġ�
//    //// ��Ӷ�����ɫ�Ķ�������
//    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
//    //glEnableVertexAttribArray(1);
//    ////������������
//    //glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
//    //glEnableVertexAttribArray(2);  /* 3Dʱ���ĸ��� */
//
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(0); 
//    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
//    glEnableVertexAttribArray(2);
//
//
//    // !--- ������ɫ�� ---��//
//    // ��ɫ������GLSL(OpenGL Shading Language)��д������ɫ��
//
//    // !--- Ƭ����ɫ�� ---��//
//    // !--- ��ɫ������ ---��// ��������ɫ���������ӵ�һ��������Ⱦ����ɫ������(Shader Program)��
//
//    Shader ourShader("./shader.vs", "./shader.fs");
//
//
//    // �õ��Ľ������һ������������ǿ��Ե���glUseProgram�������øմ����ĳ��������Ϊ���Ĳ������Լ�������������
//    // ��glUseProgram��������֮��ÿ����ɫ�����ú���Ⱦ���ö���ʹ������������Ҳ����֮ǰд����ɫ��)��
//    // ����ɫ���������ӵ���������Ժ󣬼ǵ�ɾ����ɫ���������ǲ�����Ҫ����
//
//    //glBindVertexArray(0);
//
//    // !--- �����봴������ ---��//
//    //��������
//    unsigned int texture;
//    glGenTextures(1, &texture);
//    glBindTexture(GL_TEXTURE_2D, texture);
//    //Ϊ��ǰ�󶨵�����������û��ƣ����˷�ʽ
//    /*
//        �������곬��Ĭ�Ϸ�Χʱ��ÿ��ѡ��в�ͬ���Ӿ�Ч�����, s, t, r -> x, y, z
//        �����зŴ�(Magnify)����С(Minify)������ʱ���������������˵�ѡ��
//    */
//    //float borderColor[] = { 1.0f, 0.0f, 0.0f, 1.0f };
//    //glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    //���ز���������
//    int width, height, nrChannels;
//    stbi_set_flip_vertically_on_load(true);//����ͼƬʱ����ֱ��ת
//    unsigned char* data = stbi_load("../../image/container.jpg", &width, &height, &nrChannels, 0);
//    if (data) {
//        /*
//            ��ǰ�󶨵��������ͻᱻ����������ͼ��Ȼ����Ŀǰֻ�л�������(Base-level)������ͼ�񱻼����ˣ����Ҫʹ�ö༶��Զ����
//            ֱ������������֮�����glGenerateMipmap�����Ϊ��ǰ�󶨵������Զ�����������Ҫ�Ķ༶��Զ����
//        */
//        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
//        glGenerateMipmap(GL_TEXTURE_2D);
//    }
//    else {
//        std::cout << "Failed to load texture" << std::endl;
//    }
//    //�ͷ�ͼ����ڴ���һ���ܺõ�ϰ��
//    stbi_image_free(data);
//
//    // �ڶ�������
//    unsigned int texture2;
//    glGenTextures(1, &texture2);
//    glBindTexture(GL_TEXTURE_2D, texture2);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//    //���ز���������
//    data = stbi_load("../../image/awesomeface.png", &width, &height, &nrChannels, 0);
//    if (data) {
//        /*
//            ��ǰ�󶨵��������ͻᱻ����������ͼ��Ȼ����Ŀǰֻ�л�������(Base-level)������ͼ�񱻼����ˣ����Ҫʹ�ö༶��Զ����
//            ֱ������������֮�����glGenerateMipmap�����Ϊ��ǰ�󶨵������Զ�����������Ҫ�Ķ༶��Զ����
//        */
//        // ���ͼ����͸������Ϣ����RGBA
//        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
//        glGenerateMipmap(GL_TEXTURE_2D);
//    }
//    else {
//        std::cout << "Failed to load texture" << std::endl;
//    }
//    //�ͷ�ͼ����ڴ���һ���ܺõ�ϰ��
//    stbi_image_free(data);
//
//    ourShader.use(); // ��Ҫ����������uniform����֮ǰ������ɫ������
//    glUniform1i(glGetUniformLocation(ourShader.ID, "texture1"), 0); // �ֶ�����
//    ourShader.setInt("texture2", 1); // ����ʹ����ɫ��������
//
//    //glm::mat4 trans;
//    //trans = glm::rotate(trans, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f)); // ��z����ת90�ȣ�radians(90.0f)ת���ȣ�
//    //trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 0.5f)); // ÿ���ᶼ���ŵ�0.5��
//    //// GLM���Զ���������ˣ����صĽ����һ�������˶���任�ı任����
//
//    ////��һ����uniform��λ��ֵ���ڶ�����������OpenGL���ǽ�Ҫ���Ͷ��ٸ����󡣵���������ѯ�������Ƿ�ϣ�������ǵľ������ת��(Transpose)��
//    //// ���һ�������������ľ������ݣ�����GLM�����ǰ����ǵľ��󴢴�ΪOpenGL��ϣ�����ܵ����֣��������Ҫ����GLM���Դ��ĺ���value_ptr���任��Щ���ݡ�
//    //glUniformMatrix4fv(glGetUniformLocation(ourShader.ID, "transform"), 1, GL_FALSE, glm::value_ptr(trans));
//
//    glm::mat4 model; // ǰ���transʵ���Ͼ���model���󣬶�ģ�ͽ��б任
// 
//    glm::mat4 view;
//    //view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
//    //����lookat���󣺶���һ�������λ�ã�һ��Ŀ��λ�ú�һ�������������Ϸ���
//    //view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
//    //                   glm::vec3(0.0f, 0.0f, 0.0f),
//    //                   glm::vec3(0.0f, 1.0f, 0.0f));
//
//    glm::mat4 projection;
//
//    while (!glfwWindowShouldClose(window))
//    {
//        // ����
//        processInput(window);
//
//        // ��Ⱦָ��
//        glClearColor(0.2f, 0.3f, 0.3f, 1.0f); // ����glClear֮�⣬���ǻ�������glClearColor�����������Ļ���õ���ɫ��������glClear�����������ɫ����֮��������ɫ���嶼�ᱻ���ΪglClearColor�������õ���ɫ����������ǽ���Ļ����Ϊ�����ƺڰ��������ɫ��
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // ���ܵĻ���λ��GL_COLOR_BUFFER_BIT��GL_DEPTH_BUFFER_BIT��GL_STENCIL_BUFFER_BIT
//
//        // !--- ����ͼ��  ---��//
//
//        // ����uniform��Ҫ��gluseprogram()֮��
//        // ����uniform��ɫ 
//        //float timeValue = glfwGetTime();
//        //float greenValue = sin(timeValue) / 2.0f + 0.5f;
//        //int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
//        //glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
//
//        //// ��ʱ����ת
//        //glm::mat4 trans; // ����ʵ�ʶ�����ʱ������ת����λ�ƣ���Ϊ����������ҳ�trans�����ȵľ���������tranform����ߣ�
//        //trans = glm::translate(trans, glm::vec3(0.5f, -0.5f, 0.0f));
//        //trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
//        //glUniformMatrix4fv(glGetUniformLocation(ourShader.ID, "transform"), 1, GL_FALSE, glm::value_ptr(trans));
//
//        //model = glm::rotate(model, (float)glfwGetTime() * 0.0002f, glm::vec3(0.5f, 1.0f, 0.0f));
//        glm::mat4 clip_space;
//        //glUniformMatrix4fv(glGetUniformLocation(ourShader.ID, "clip_space"), 1, GL_FALSE, &clip_space[0][0]);
//
//
//        // ������ // �Ȱ�����������Ӧ������Ԫ��Ȼ�����ĸ�uniform��������Ӧ�ĸ�����Ԫ��
//        glActiveTexture(GL_TEXTURE0);  // Ĭ�ϼ����
//        glBindTexture(GL_TEXTURE_2D, texture);
//        glActiveTexture(GL_TEXTURE1);
//        glBindTexture(GL_TEXTURE_2D, texture2);
//
//        ourShader.setFloat("rate", rate);
//
//        // ����a
//        glBindVertexArray(VAO);
//        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//        //glDrawArrays(GL_TRIANGLES, 0, 36);
//
//          //�����Ȧת����view
//        //float radius = 10.0f;
//        //float camX = sin(glfwGetTime()) * radius;
//        //float camZ = cos(glfwGetTime()) * radius;
//        //view = glm::lookAt(glm::vec3(camX, 0.0f, camZ),
//        //    glm::vec3(0.0f, 0.0f, 0.0f),
//        //    glm::vec3(0.0f, 1.0f, 0.0f));
//
//        //view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);//cameraFront��Ŀ�ӷ���ָ���Ƿ��򣬴�С����ν
//        view = camera.GetViewMatrix();
//        projection = glm::perspective(glm::radians(camera.Zoom), (float)(screenWidth / screenHeight), 0.1f, 100.0f);
//        // ��Ұ(Field of View)��fov���������ǿ��Կ��������ж��ķ�Χ������Ұ��Сʱ������ͶӰ�����Ŀռ�ͻ��С�������Ŵ�(Zoom In)�˵ĸо�
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
//        //// �ڶ������� ��ʱ������
//        //trans = glm::mat4(1.0f);
//        //trans = glm::translate(trans, glm::vec3(-0.5f, 0.5f, 0.0f));
//        //float scalerate = sin(glfwGetTime()) >= 0 ? sin(glfwGetTime()) : -sin(glfwGetTime());
//        //trans = glm::scale(trans, glm::vec3(scalerate, scalerate, scalerate));
//        //glUniformMatrix4fv(glGetUniformLocation(ourShader.ID, "transform"), 1, GL_FALSE, glm::value_ptr(trans));
//        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//
//        // ��鲢�����¼�����������
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
//    glfwTerminate(); // �ͷ�֮ǰ�������Դ
//
//    return 0;
//}