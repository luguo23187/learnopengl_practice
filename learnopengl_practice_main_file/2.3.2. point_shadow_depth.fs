#version 330 core
in vec4 FragPos;

uniform vec3 lightPos;
uniform float far_plane;

void main(){
	// 获取片段和光源之间的距离
	float lightDistance = length(FragPos.xyz - lightPos);

	// 通过除以far_plane映射到[0;1]范围
	lightDistance = lightDistance / far_plane;

	// 将其写入修改后的深度
	gl_FragDepth = lightDistance;
}

// 使用这些着色器渲染场景，立方体贴图附加的帧缓冲对象激活以后，你会得到一个完全填充的深度立方体贴图，以便于进行第二阶段的阴影计算。