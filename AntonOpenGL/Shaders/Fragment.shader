#version 330 core

// this is the color this shader will output
out vec4 frag_color;
in vec3 color;

void main() 
{
	frag_color = vec4(color, 1.0);
}