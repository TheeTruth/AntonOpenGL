#version 330 core

layout(location = 0) in vec3 position;

//uniform mat4 model_matrix;

void main()
{
	// gl_Position will determine the position of the vertices
	gl_Position = vec4(position, 1.0);
}