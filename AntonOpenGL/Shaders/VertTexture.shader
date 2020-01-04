#version 330 core
layout(location = 0) in vec3 vertex_position_modelSpace;
layout(location = 1) in vec2 aTexCoord;
layout(location = 2) in vec3 normals;

out vec2 texCoord;
uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * vec4(vertex_position_modelSpace, 1.0);
	texCoord = aTexCoord;
}