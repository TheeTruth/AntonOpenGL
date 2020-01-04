#version 330 core

// this is the color this shader will output
out vec4 frag_color;

//we take this in from the vertex shader
in vec2 texCoord;

uniform sampler2D ourTexture;
uniform vec3 lightColor;
float ambientIntensity = 0.5f;

void main()
{
	
	vec4 objectColor = texture(ourTexture, texCoord);
	vec3 ambient = ambientIntensity * lightColor;
	//frag_color determines the color of the pixel
	frag_color = vec4(ambient, 1.0f) * objectColor;
}