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
//    Shader shader("1.10. instancing.vs", "1.10. instancing.fs");
//    Shader instanceshader("1.10. rock_instancing.vs", "1.10. rock_instancing.fs");
//
//    //!!!!!!--------model part-------!!!!!!!//
//    // load model
//    Model planet("../../sample_model/planet/planet.obj");
//    Model rock("../../sample_model/rock/rock.obj");
//
//    unsigned int amount = 5000;
//    glm::mat4* modelMatrices;
//    modelMatrices = new glm::mat4[amount];
//    srand(glfwGetTime()); // ��ʼ���������    
//    float radius = 25.0;
//    float offset = 2.5f;
//    for (unsigned int i = 0; i < amount; i++)
//    {
//        glm::mat4 model;
//        // 1. λ�ƣ��ֲ��ڰ뾶Ϊ 'radius' ��Բ���ϣ�ƫ�Ƶķ�Χ�� [-offset, offset]
//        float angle = (float)i / (float)amount * 360.0f;
//        float displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
//        float x = sin(angle) * radius + displacement;
//        displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
//        float y = displacement * 0.4f; // �����Ǵ��ĸ߶ȱ�x��z�Ŀ��ҪС
//        displacement = (rand() % (int)(2 * offset * 100)) / 100.0f - offset;
//        float z = cos(angle) * radius + displacement;
//        model = glm::translate(model, glm::vec3(x, y, z));
//
//        // 2. ���ţ��� 0.05 �� 0.25f ֮������
//        float scale = (rand() % 20) / 100.0f + 0.05;
//        model = glm::scale(model, glm::vec3(scale));
//
//        // 3. ��ת������һ�����룩���ѡ�����ת�����������������ת
//        float rotAngle = (rand() % 360);
//        model = glm::rotate(model, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));
//
//        // 4. ��ӵ������������
//        modelMatrices[i] = model;
//    }
//
//    // ���ǲ���ʹ��ģ��uniform��������Ϊһ��mat4�Ķ������ԣ��������ܹ��洢һ��ʵ��������ı任����Ȼ���������Ƕ������Ե����ʹ���vec4ʱ����Ҫ�����һ�������ˡ�
//    // �������������������ݴ�С����һ��vec4����Ϊһ��mat4��������4��vec4��������ҪΪ�������Ԥ��4���������ԡ�
//    // ��Ϊ���ǽ�����λ��ֵ����Ϊ3������ÿһ�еĶ�������λ��ֵ����3��4��5��6��
//    // ���㻺�����
//    unsigned int buffer;
//    glGenBuffers(1, &buffer);
//    glBindBuffer(GL_ARRAY_BUFFER, buffer);
//    glBufferData(GL_ARRAY_BUFFER, amount * sizeof(glm::mat4), &modelMatrices[0], GL_STATIC_DRAW);
//    // ע���������ǽ�Mesh��VAO��˽�б�����Ϊ�˹��б������������ܹ��������Ķ�����������Ⲣ������õĽ��������ֻ��Ϊ����ϱ�С�ڵ�һ���򵥵ĸĶ���
//    for (unsigned int i = 0; i < rock.meshes.size(); i++)
//    {
//        unsigned int VAO = rock.meshes[i].VAO;
//        glBindVertexArray(VAO);
//        // ��������
//        GLsizei vec4Size = sizeof(glm::vec4);
//        glEnableVertexAttribArray(3);
//        glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)0);
//        glEnableVertexAttribArray(4);
//        glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(vec4Size));
//        glEnableVertexAttribArray(5);
//        glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(2 * vec4Size));
//        glEnableVertexAttribArray(6);
//        glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, 4 * vec4Size, (void*)(3 * vec4Size));
//
//        glVertexAttribDivisor(3, 1);
//        glVertexAttribDivisor(4, 1);
//        glVertexAttribDivisor(5, 1);
//        glVertexAttribDivisor(6, 1);
//
//        glBindVertexArray(0);
//    }
//
//    //!!!!!!!!!!!!!---------quad part--------!!!!!!!!//
//    // set up vertex data (and buffer(s)) and configure vertex attributes
//    // ------------------------------------------------------------------
//    float quadVertices[] = {
//        // λ��          // ��ɫ
//        -0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
//         0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
//        -0.05f, -0.05f,  0.0f, 0.0f, 1.0f,
//
//        -0.05f,  0.05f,  1.0f, 0.0f, 0.0f,
//         0.05f, -0.05f,  0.0f, 1.0f, 0.0f,
//         0.05f,  0.05f,  0.0f, 1.0f, 1.0f
//    };
//    //// instance offset
//    //glm::vec2 translations[100];
//    //int index = 0;
//    //float offset = 0.1f;
//    //for (int y = -10; y < 10; y += 2)
//    //{
//    //    for (int x = -10; x < 10; x += 2)
//    //    {
//    //        glm::vec2 translation;
//    //        translation.x = (float)x / 10.0f + offset;
//    //        translation.y = (float)y / 10.0f + offset;
//    //        translations[index++] = translation;
//    //    }
//    //}
//    //// VAO
//    //unsigned int quadVAO, quadVBO;
//    //glGenVertexArrays(1, &quadVAO);
//    //glGenBuffers(1, &quadVBO);
//    //glBindVertexArray(quadVAO);
//    //glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
//    //glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
//    //glEnableVertexAttribArray(0);
//    //glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
//    //glEnableVertexAttribArray(1);
//    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));
//    //
//
//    //// ��Ϊʵ���������position��color����һ�������Ƕ������ԣ����ǻ���Ҫ���������ݴ��ڶ��㻺������У�����������������ָ�롣
//    //// �������Ƚ�����һ���ֵģ�translations����浽һ���µĻ��������
//    //unsigned int instanceVBO;
//    //glGenBuffers(1, &instanceVBO);
//    //glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
//    //glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * 100, &translations[0], GL_STATIC_DRAW);
//    //glBindBuffer(GL_ARRAY_BUFFER, 0);
//    //// ���ö�������ָ�룬�����ö�������
//    //glEnableVertexAttribArray(2);
//    //glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
//    //glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
//    //glBindBuffer(GL_ARRAY_BUFFER, 0);
//    //glVertexAttribDivisor(2, 1); // �������������OpenGL��ʲôʱ����¶������Ե���������һ�����ݡ����ĵ�һ����������Ҫ�Ķ������ԣ��ڶ������������Գ���(Attribute Divisor)��
//    //// Ĭ������£����Գ�����0������OpenGL������Ҫ�ڶ�����ɫ����ÿ�ε���ʱ���¶������ԡ�
//    //// ��������Ϊ1ʱ�����Ǹ���OpenGL����ϣ������Ⱦһ����ʵ����ʱ����¶������ԡ�
//    //// ������Ϊ2ʱ������ϣ��ÿ2��ʵ������һ�����ԣ�
//    //// �Դ����ơ����ǽ����Գ�������Ϊ1�����ڸ���OpenGL������λ��ֵ2�Ķ���������һ��ʵ�������顣(���ҲҪ��glDrawArraysInstanced������)
//    //glBindVertexArray(0);
//
//    // load textures
//    // -------------
//
//    // shader configuration
//    // --------------------
//
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
//        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//
//        //!!!!!!!!----------quad part-------!!!!!//
//        //// ��100��ƫ����������vertexshader
//        //shader.use();
//        ///*for (unsigned int i = 0; i < 100; i++)
//        //{
//        //    stringstream ss;
//        //    string index;
//        //    ss << i;
//        //    index = ss.str();
//        //    shader.setVec2(("offsets[" + index + "]").c_str(), translations[i]);
//        //}*/
//
//        //glBindVertexArray(quadVAO);
//        //glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 100); // �������ֱ�ʾʵ�����������������ܳ�����ɫ����uniform��������
//        ////glDrawArrays(GL_TRIANGLES, 0, 6);
//        //glBindVertexArray(0);
//
//
//        //!!!!!!!!----------model part-------!!!!!//
//        // ��������
//        shader.use();
//        glm::mat4 view = camera.GetViewMatrix();
//        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
//        shader.setMat4("view", view);
//        shader.setMat4("projection", projection);
//        glm::mat4 model;
//        model = glm::translate(model, glm::vec3(0.0f, -3.0f, 0.0f));
//        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
//        shader.setMat4("model", model);
//        planet.Draw(shader);
//
//        //// ����С����
//        //for (unsigned int i = 0; i < amount; i++)
//        //{
//        //    shader.setMat4("model", modelMatrices[i]);
//        //    rock.Draw(shader);
//        //}
//
//        instanceshader.use();
//        instanceshader.setMat4("view", view);
//        instanceshader.setMat4("projection", projection);
//        instanceshader.setMat4("model", model);
//        //asteroidShader.setInt("texture_diffuse1", 0);
//        // ����С����
//        
//        for (unsigned int i = 0; i < rock.meshes.size(); i++)
//        {
//            glBindVertexArray(rock.meshes[i].VAO);
//            glDrawElementsInstanced(
//                GL_TRIANGLES, rock.meshes[i].indices.size(), GL_UNSIGNED_INT, 0, amount
//            );
//        }
//
//
//        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
//        // -------------------------------------------------------------------------------
//        glfwSwapBuffers(window);
//        glfwPollEvents();
//    }
//
//    // optional: de-allocate all resources once they've outlived their purpose:
//    // ------------------------------------------------------------------------
//    //glDeleteVertexArrays(1, &quadVAO);
//    //glDeleteBuffers(1, &quadVBO);
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