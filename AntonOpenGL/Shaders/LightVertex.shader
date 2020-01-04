#version 330 core

layout(location = 0) in vec3 vertex_position_modelSpace;

uniform mat4 u_MVP;

void main()
{
	// gl_Position will determine the position of the vertices
	gl_Position = u_MVP * vec4(vertex_position_modelSpace, 1.0);
}