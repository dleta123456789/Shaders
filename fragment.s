#version 330 core
out vec4 FragColor;
in vec4 vertex_postion; 
in vec3 ourColor;
void main()
{
	//FragColor = vec4(ourColor, 1.0f);
	FragColor=vertex_postion;
};