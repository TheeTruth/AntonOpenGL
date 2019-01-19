#version 330 core

// this is the color this shader will output
out vec4 v4color;

void main() 
{
	vec3 color = vec3(1, 0, 0);
	v4color = vec4(color, 1.0f);
}