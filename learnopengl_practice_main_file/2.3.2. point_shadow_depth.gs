#version 330 core
layout(triangles) in;
layout(triangle_strip, max_vertices = 18) out;

uniform mat4 shadowMatrices[6];

out vec4 FragPos; 

void main(){
	for(int face = 0; face < 6; face++){
		gl_Layer = face; // ������ɫ����һ���ڽ���������gl_Layer����ָ����ɢ������ͼ���͵���������ͼ���ĸ���
		// ������ɫ���ͻ�������һ�������Ļ���ͼ�η��͵����͹ܵ�����һ�׶Σ�
		// �������Ǹ�������������ܿ���ÿ������ͼ�ν���Ⱦ����������ͼ����һ���档
		// ��Ȼ��ֻ�е���������һ�����ӵ������֡�������������ͼ�������Ч��
		for(int i = 0; i < 3; i++){
			FragPos = gl_in[i].gl_Position;
			gl_Position = shadowMatrices[face] * FragPos;
			EmitVertex();
		}
		EndPrimitive();
	}
}

/*
	��main�����У����Ǳ�����������ͼ��6���棬����ÿ����ָ��Ϊһ������棬��������interger���������浽gl_Layer��
	Ȼ������ͨ������Ĺ�ռ�任�������FragPos����ÿ������ռ䶥��任����صĹ�ռ䣬����ÿ�������Ρ�
	ע�⣬���ǻ�Ҫ������FragPos�������͸�������ɫ����������Ҫ����һ�����ֵ��
*/