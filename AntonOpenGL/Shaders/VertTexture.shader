#version 330 core
layout(location = 0) in vec3 vertex_position_modelSpace;
layout(location = 1) in vec2 aTexCoord;
layout(location = 2) in vec3 normals;

out vec2 texCoord;
uniform mat4 model_matrix;

void main()
{
	gl_Position = model_matrix * vec4(vertex_position_modelSpace, 1.0);
	texCoord = aTexCoord;
}