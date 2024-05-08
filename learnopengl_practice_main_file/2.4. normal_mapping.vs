#version 330 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;
layout (location = 3) in vec3 tangent;
layout (location = 4) in vec3 bitangent;

out VS_OUT {
	vec3 FragPos;
	vec2 TexCoords;
	vec3 TangentLightPos;
	vec3 TangentViewPos;
	vec3 TangentFragPos;
} vs_out;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

uniform vec3 lightPos;
uniform vec3 viewPos;

void main(){
	gl_Position = projection * view * model * vec4(position, 1.0f);
	vs_out.FragPos = vec3(model * vec4(position, 1.0));
	vs_out.TexCoords = texCoords;

	// 然后我们创建实际的TBN矩阵，直接把相应的向量应用到mat3构造器就行。
	// 注意，如果我们希望更精确的话就不要将TBN向量乘以model矩阵，而是使用法线矩阵，因为我们只关心向量的方向，不关心平移和缩放。
	// vec3 T = normalize(vec3(model * vec4(tangent,   0.0)));
    // vec3 B = normalize(vec3(model * vec4(bitangent, 0.0)));
    // vec3 N = normalize(vec3(model * vec4(normal,    0.0)));

	// 法线矩阵
	mat3 normalMatrix = transpose(inverse(mat3(model)));
    vec3 T = normalize(normalMatrix * tangent);
    vec3 B = normalize(normalMatrix * bitangent);
    vec3 N = normalize(normalMatrix * normal);  

	mat3 TBN = transpose(mat3(T, B, N)); // TBN是正交矩阵
	vs_out.TangentLightPos = TBN * lightPos;
	vs_out.TangentViewPos  = TBN * viewPos;
    vs_out.TangentFragPos  = TBN * vs_out.FragPos;
}
/*
	现在我们有了TBN矩阵，如果来使用它呢？通常来说有两种方式使用它，我们会把这两种方式都说明一下：

 1、我们直接使用TBN矩阵，这个矩阵可以把切线坐标空间的向量转换到世界坐标空间。
	因此我们把它传给片段着色器中，把通过采样得到的法线坐标左乘上TBN矩阵，转换到世界坐标空间中，
	这样所有法线和其他光照变量就在同一个坐标系中了。

 2、我们也可以使用TBN矩阵的逆矩阵，这个矩阵可以把世界坐标空间的向量转换到切线坐标空间。
	因此我们使用这个矩阵左乘其他光照变量，把他们转换到切线空间，
	这样法线和其他光照变量再一次在一个坐标系中了。
	（因为lightPos和viewPos不是每个fragment运行都要改变，对于fs_in.FragPos，我们也可以在顶点着色器计算它的切线空间位置。）
	（现在不是把TBN矩阵的逆矩阵发送给像素着色器，而是将切线空间的光源位置，观察位置以及顶点位置发送给像素着色器）
*/