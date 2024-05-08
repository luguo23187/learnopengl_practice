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
     
     // ����
     // vec3 I = normalize(Position - cameraPos); // �۲췽��
     // vec3 R = reflect(I, normalize(Normal)); // ���䷽��(���ⷽ��) // reflect�Դ��ķ��亯��
     // FragColor = vec4(texture(skybox, R).rgb, 1.0);

     // ����(��������)
     float ratio = 1.00 / 1.52; // ������������
     vec3 I = normalize(Position - cameraPos);
     vec3 R = refract(I, normalize(Normal), ratio); // refract��glsl�Դ������亯��
     FragColor = vec4(texture(skybox, R).rgb, 1.0);
}