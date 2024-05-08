#version 330 core
out vec4 FragColor;

// in vec2 TexCoords;
in vec3 Normal;
in vec3 Position;

uniform vec3 cameraPos;
// uniform sampler2D texture1;
uniform samplerCube skybox;

float near = 0.1;
float far = 100.0;

void main()
{    
     // FragColor = texture(texture1, TexCoords);
     
     // 反射
     // vec3 I = normalize(Position - cameraPos); // 观察方向
     // vec3 R = reflect(I, normalize(Normal)); // 反射方向(进光方向) // reflect自带的反射函数
     // FragColor = vec4(texture(skybox, R).rgb, 1.0);

     // 折射(单面折射)
     float ratio = 1.00 / 1.52; // 玻璃的折射率
     vec3 I = normalize(Position - cameraPos);
     vec3 R = refract(I, normalize(Normal), ratio); // refract是glsl自带的折射函数
     FragColor = vec4(texture(skybox, R).rgb, 1.0);
}