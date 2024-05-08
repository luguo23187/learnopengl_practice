#version 330 core

out vec4 FragColor;
// in vec3 ourColor; /* 3D时做的更改 */
in vec2 TexCoord;

// uniform vec4 ourColor;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float rate;

void main()
{
    // FragColor = vec4(ourColor, 1.0);
    // GLSL内建的texture函数来采样纹理的颜色，它第一个参数是纹理采样器，第二个参数是对应的纹理坐标。
    // texture函数会使用之前设置的纹理参数对相应的颜色值进行采样。这个片段着色器的输出就是纹理的（插值）纹理坐标上的(过滤后的)颜色。
    // FragColor = texture(texture2, TexCoord);
    // 进行颜色混合
    // FragColor = texture(texture1, TexCoord) * vec4(ourColor, 1.0);
    // 进行纹理混合
    //FragColor = mix(texture(texture1, TexCoord),texture(texture2, TexCoord), 0.2);
    FragColor = mix(texture(texture1, TexCoord),texture(texture2, vec2(1.0 - TexCoord.x, TexCoord.y)), rate);
}