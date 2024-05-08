#version 330 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D texture1;

float near = 0.1;
float far = 100.0;

float LinearizDepth(float depth){
    float z = depth * 2.0 - 1.0; // 变成[-1, 1]
    return (2.0 * near * far) / (far + near - z * (far - near)); // 将原本非线性的计算出的深度值，逆变换成线性对应的深度值
}

void main()
{    
     FragColor = texture(texture1, TexCoords);
    // FragColor = vec4(vec3(gl_FragCoord.z), 1.0); // 直接展示深度值
    // float depth = LinearizDepth(gl_FragCoord.z) / far; // 将计算出的深度值除深度
    // FragColor = vec4(vec3(depth), 1.0);
}