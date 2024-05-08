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
//// light
//glm::vec3 lightPos(1.2f, 1.0f, 2.0f);
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
//    // 1�� ���÷����VAO��VBO
//    unsigned int VBO, cubeVAO;
//    glGenVertexArrays(1, &cubeVAO);
//    glGenBuffers(1, &VBO);
//
//    glBindBuffer(GL_ARRAY_BUFFER, VBO);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//    glBindVertexArray(cubeVAO);
//
//    // ��������
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
//    glEnableVertexAttribArray(1);
//    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
//    glEnableVertexAttribArray(2);
//
//    // 2�� ���õƹ��VAO��VBO���ֲ���;�ƹ����Ķ�����ͬ��Ҳ��3D�����壩
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
//    glm::mat4 model; // ǰ���transʵ���Ͼ���model���󣬶�ģ�ͽ��б任
//
//    glm::mat4 view;
//    glm::mat4 projection;
//
//
//    // ��������
//    unsigned int diffuseMap = loadTexture("../../image/container2.png");
//    unsigned int specularMap = loadTexture("../../image/container2_specular.png");
//    unsigned int emissionMap = loadTexture("../../image/matrix.jpg");
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
//        glm::vec3 lightColor = glm::vec3(1.0f);
//        // !--- ����ͼ��  ---��//
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
//        // ��������������
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D, diffuseMap);
//        glActiveTexture(GL_TEXTURE1);
//        glBindTexture(GL_TEXTURE_2D, specularMap);
//        glActiveTexture(GL_TEXTURE2);
//        glBindTexture(GL_TEXTURE_2D, emissionMap);
//
//        // ʵ����Ⱦ����
//        glBindVertexArray(cubeVAO);
//        //glDrawArrays(GL_TRIANGLES, 0, 36); 
//        for (int i = 0; i < 10; i++) {
//            glm::mat4 model = glm::mat4(1.0f); // ѭ��ǰ��ʼ��
//            model = glm::translate(model, cubePositions[i]);
//            float angle = 20.0f * i;
//            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
//            ourShader.setMat4("model", model);
//            glDrawArrays(GL_TRIANGLES, 0, 36);
//        }
//
//        
//        // ��Դ //
//            // ��Դ��Ȧ
//        //float radius = pow((lightPos.x * lightPos.x + lightPos.y * lightPos.y),0.5);
//        //lightPos.x = sin(currentFrame) * radius;
//        //lightPos.y = cos(currentFrame) * radius;
//
//        lightCubeShader.use();
//        lightCubeShader.setMat4("view", view);
//        lightCubeShader.setMat4("projection", projection);
//        // ʵ����Ⱦ�ƹ�
//        glBindVertexArray(lightCubeVAO);
//        for (int i = 0; i < 4; i++) {
//            lightCubeShader.setVec3("lightColor", pointLightColors[i]);
//            glm::mat4 model = glm::mat4(1.0f); // ѭ��ǰ��ʼ��
//            model = glm::translate(model, pointLightPositions[i]);
//            model = glm::scale(model, glm::vec3(0.2f)); // Make it a smaller cube
//            lightCubeShader.setMat4("model", model);
//            glDrawArrays(GL_TRIANGLES, 0, 36);
//        }
//       
//        // ��鲢�����¼�����������
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
//    glfwTerminate(); // �ͷ�֮ǰ�������Դ
//
//    return 0;
//}
//
///*
//    // ���� //
//        ourShader.use();        
//        //ourShader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
//        //ourShader.setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
//        ourShader.setInt("material.diffuse", 0); // �൱���ǰѴ�ɫ���������滻Ϊ�����к�ɫ������ɫ����vec3(0.0)���޸߹⣩����ɫ������ɫ����vec3(0.5)���ٸ߹⣩
//        //ourShader.setVec3("material.specular", 0.5f, 0.5f, 0.5f);
//        ourShader.setInt("material.specular", 1); // �൱�Ƕ�specularMapͼƬ���в�����������
//        // ourShader.setVec3("light.position", lightPos); // ͳһ��������Ҫ��shader��������֮��
//        // ourShader.setVec3("light.direction", -0.2f, -1.0f, -0.3f);
//        ourShader.setVec3("light.position", camera.Position); // ��Ϊ�۹��Ҫ��
//        ourShader.setVec3("light.direction", camera.Front);
//        ourShader.setFloat("light.cutOff", glm::cos(glm::radians(12.5f))); // �ýǶ�ֵ������һ������ֵ�����㴫��FragShader�Ƚ�
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
//        ourShader.setFloat("material.shininess", 32.0f); // �ṹ��ֻ�ǳ䵱uniform�����ǵ�һ�������ռ䡣����������������ṹ��Ļ������Ǳ�������ÿ��������uniform����Ҫ�Խṹ����Ϊǰ׺��
//        //ourShader.setInt("material.emission", 2);
//
//        //glm::vec3 lightColor = glm::vec3(1.0f);
//
//        //glm::vec3 diffuseColor = 0.8f * lightColor;
//        //glm::vec3 ambientColor = 0.1f * diffuseColor;
//*/