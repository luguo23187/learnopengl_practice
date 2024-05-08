# learnopengl_practice
Records of learning opengl through the learnopengl project.

OpenGL practice records based on [learnopengl tutorials](https://learnopengl.com/).

### Libraries used
We've used a couple of built-in libraries and glad, glfw, glm libraries:

```
#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
```

In other hand, to talk about how it works and what is its structure. Firstly, we can see our folders such as:
1. [/Shaders](https://github.com/alexjr2001/RubikCube_OpenGL/tree/main/shaders): Where we work with two types of them, the vector shader [shader.vs](https://github.com/alexjr2001/RubikCube_OpenGL/blob/main/shaders/shader.vs) which is able to manipulate any of the corner vertices, I mean we manage the rendering with this and the fragment shader [shader.fs](https://github.com/alexjr2001/RubikCube_OpenGL/blob/main/shaders/shader.fs) where we can modify how the space between the vertices look like (colors, textures, etc.).

2. [/texture](https://github.com/alexjr2001/RubikCube_OpenGL/tree/main/texture): It is the place where we store all the images(textures) that we would want to see in our faces of a rendering. We have to understand the fragment shader in order to work with both together, thus we can achieve a good-looking object.

3. [/src](https://github.com/alexjr2001/RubikCube_OpenGL/tree/main/src): The most important folder because it is where all the magic occurs, we have all the files of the source code.
    - Main and Global: In [main.cpp](https://github.com/alexjr2001/RubikCube_OpenGL/blob/main/src/main.cpp) we call [global.cpp](https://github.com/alexjr2001/RubikCube_OpenGL/blob/main/src/global.h) where we initialize all the OpenGL Window, the menu, we load the textures and we manage all the input callbacks.
    - [Cubito.h](https://github.com/alexjr2001/RubikCube_OpenGL/blob/main/src/Cubito.h) and [Cubito.cpp](https://github.com/alexjr2001/RubikCube_OpenGL/blob/main/src/Cubito.cpp): It's where we have our cube class.
    - [Camara.h](https://github.com/alexjr2001/RubikCube_OpenGL/blob/main/src/Camera.h) and [Camera.cpp](https://github.com/alexjr2001/RubikCube_OpenGL/blob/main/src/Camera.cpp): It's where we have our small camera class.
    - [Shader_s.h](https://github.com/alexjr2001/RubikCube_OpenGL/blob/main/src/shader_s.h), [glad.c](https://github.com/alexjr2001/RubikCube_OpenGL/blob/main/src/glad.c) and [stb_image.h](https://github.com/alexjr2001/RubikCube_OpenGL/blob/main/src/stb_image.h): Shader class and stb_image provided by LearnOpenGL.
    - [/Solver](https://github.com/alexjr2001/RubikCube_OpenGL/tree/main/src/Solver): It is the solver applied in our Rubik's cube, where we pass as a parameter a std::vector<std::string> of the current shuffle and it returns the solution with the same type of container. It was extracted from [hkociemba's repository](https://github.com/hkociemba?tab=repositories)
