#version 330 core
in vec4 FragPos;

uniform vec3 lightPos;
uniform float far_plane;

void main(){
	// ��ȡƬ�κ͹�Դ֮��ľ���
	float lightDistance = length(FragPos.xyz - lightPos);

	// ͨ������far_planeӳ�䵽[0;1]��Χ
	lightDistance = lightDistance / far_plane;

	// ����д���޸ĺ�����
	gl_FragDepth = lightDistance;
}

// ʹ����Щ��ɫ����Ⱦ��������������ͼ���ӵ�֡������󼤻��Ժ����õ�һ����ȫ���������������ͼ���Ա��ڽ��еڶ��׶ε���Ӱ���㡣