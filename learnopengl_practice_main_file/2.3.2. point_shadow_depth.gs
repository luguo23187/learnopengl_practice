#version 330 core
layout(triangles) in;
layout(triangle_strip, max_vertices = 18) out;

uniform mat4 shadowMatrices[6];

out vec4 FragPos; 

void main(){
	for(int face = 0; face < 6; face++){
		gl_Layer = face; // 几何着色器有一个内建变量叫做gl_Layer，它指定发散出基本图形送到立方体贴图的哪个面
		// 几何着色器就会像往常一样把它的基本图形发送到输送管道的下一阶段，
		// 但当我们更新这个变量就能控制每个基本图形将渲染到立方体贴图的哪一个面。
		// 当然这只有当我们有了一个附加到激活的帧缓冲的立方体贴图纹理才有效：
		for(int i = 0; i < 3; i++){
			FragPos = gl_in[i].gl_Position;
			gl_Position = shadowMatrices[face] * FragPos;
			EmitVertex();
		}
		EndPrimitive();
	}
}

/*
	在main函数中，我们遍历立方体贴图的6个面，我们每个面指定为一个输出面，把这个面的interger（整数）存到gl_Layer。
	然后，我们通过把面的光空间变换矩阵乘以FragPos，将每个世界空间顶点变换到相关的光空间，生成每个三角形。
	注意，我们还要将最后的FragPos变量发送给像素着色器，我们需要计算一个深度值。
*/