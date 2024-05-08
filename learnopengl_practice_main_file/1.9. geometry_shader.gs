#version 330 core
layout (triangles) in; // 声明从顶点着色器输入的图元类型
layout (triangle_strip, max_vertices = 3) out; // 指定几何着色器输出图元类型

out vec3 fColor;

// gl_in[]是传入的一个接口块，一个数组，包含传入的片元的所有点(传入三角形就是3个数组) // 默认有的

// in gl_Vertex
// {
//  	vec4 gl_Position;
//  	float gl_Pointsize;
//  	float gl_ClipDistance[];
// } gl_in[];

in VS_OUT {
    vec2 texCoords;
} gs_in[]; // 因为传入的是一组顶点，定义用数组的形式接收

out vec2 TexCoords;

uniform float time;

vec4 explode(vec4 position, vec3 normal){
    float magnitude = 0.5;
    vec3 direction = normal * ((sin(time) + 1.0) / 2.0) * magnitude;
    return position + vec4(direction, 0.0);
}

vec3 GetNormal()
{
   vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
   vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
   return normalize(cross(a, b));
}

void main(){
    vec3 normal = GetNormal();

    gl_Position = explode(gl_in[0].gl_Position, normal);
    TexCoords = gs_in[0].texCoords;
    EmitVertex();
    gl_Position = explode(gl_in[1].gl_Position, normal);
    TexCoords = gs_in[1].texCoords;
    EmitVertex();
    gl_Position = explode(gl_in[2].gl_Position, normal);
    TexCoords = gs_in[2].texCoords;
    EmitVertex();

    EndPrimitive();
}