#version 330 core

// this is the color this shader will output
out vec4 frag_color;

//we take this in from the vertex shader
in vec2 texCoord;

uniform sampler2D ourTexture;

void main()
{
	//frag_color determines the color of the pixel
	frag_color = texture(ourTexture, texCoord);
}