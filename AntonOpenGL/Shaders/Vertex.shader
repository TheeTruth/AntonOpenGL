#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 in_color;

out vec3 color;
uniform mat4 model_matrix;

void main() 
{
	// gl_Position will determine the position of the vertices
	gl_Position = model_matrix * vec4(vertexPosition_modelspace, 1.0);
	color = in_color;
}
