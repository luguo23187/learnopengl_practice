# learnopengl_practice
Records of learning opengl through the learnopengl project.

OpenGL practice records based on [learnopengl tutorials](https://learnopengl.com/).

### Libraries used
Several designated third-party libraries are used according to learnopengl:

```
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
```

### File and folder description
Note: The file path in the file is the relative path of the local machine.
1. [/learnopengl_practice_main_file](https://github.com/luguo23187/learnopengl_practice/tree/main/learnopengl_practice_main_file):This folder contains the code guided in [learnopengl tutorials](https://learnopengl.com/), including building packages for opengl objects, cameras, etc., multi-object multi-light rendering, frame buffering, and sky boxes, where files with a.vs suffix are slice shaders, files with a.fs suffix are fragment shaders, and files with a.gs suffix are geometry shaders.

2. [/sample_model](https://github.com/luguo23187/learnopengl_practice/tree/main/sample_model): This folder contains the model and texture files contained in the Loading Models chapter of [learnopengl tutorials](https://learnopengl.com/).

3. [/image](https://github.com/luguo23187/learnopengl_practice/tree/main/image): This folder contains the texture files used in [learnopengl tutorials](https://learnopengl.com/).

### Practice demo
#### Rubik's cube simulator
A Rubik's cube was simulated with opengl and related third-party libraries. Keys could be used to rotate the cube, mouse and arrow keys could be used to move the Angle of view, and Thislethwaite method was used to give the restoration path in the disturbed state, and the cube was animated.

The files are located in the [/learnopengl_practice_main_file](https://github.com/luguo23187/learnopengl_practice/tree/main/learnopengl_practice_main_file), include [application_for_rubikcube.cpp](https://github.com/luguo23187/learnopengl_practice/blob/main/learnopengl_practice_main_file/application_for_rubikcube.cpp), [Makecube.cpp](https://github.com/luguo23187/learnopengl_practice/blob/main/learnopengl_practice_main_file/MakeCube.cpp), [Makecube.h](https://github.com/luguo23187/learnopengl_practice/blob/main/learnopengl_practice_main_file/MakeCube.h) and files in [/learnopengl_practice_main_file/solve](https://github.com/luguo23187/learnopengl_practice/tree/main/learnopengl_practice_main_file/solve).

![Menu](https://github.com/luguo23187/learnopengl_practice/assets/103297770/09c7cc30-e649-44de-b9d1-67414faddc40)
![Simulated Rubik's cube](https://github.com/luguo23187/learnopengl_practice/assets/103297770/9d399a19-2c82-4fe6-a90c-a626cb05f3e3)
![Simulated Rubik's cube](https://github.com/luguo23187/learnopengl_practice/assets/103297770/1361e5d5-9733-41f0-81df-3faa8c0bbe15)
