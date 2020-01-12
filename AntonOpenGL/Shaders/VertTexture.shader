#version 330 core
layout(location = 0) in vec3 vertex_position_modelSpace;
layout(location = 1) in vec2 aTexCoord;
layout(location = 2) in vec3 aNormal;

out vec2 texCoord;
out vec3 normal;
out vec3 fragPos;
uniform vec3 model;
uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * vec4(vertex_position_modelSpace, 1.0);
	fragPos = vec3(model * vertex_position_modelSpace);
	texCoord = aTexCoord;
	normal = aNormal;
}