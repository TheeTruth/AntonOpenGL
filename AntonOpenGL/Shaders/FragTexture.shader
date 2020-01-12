#version 330 core

// this is the color this shader will output
out vec4 frag_color;

//we take this in from the vertex shader
in vec2 texCoord;
in vec3 fragPos;
in vec3 normal;
uniform sampler2D ourTexture;

uniform vec3 lightPosition;
uniform vec3 lightColor;
float ambientIntensity = 0.2f;

void main()
{
	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(lightPosition - fragPos);
	float diff = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = diff * lightColor;
	vec4 objectColor = texture(ourTexture, texCoord);
	vec3 ambient = ambientIntensity * lightColor;
	vec3 result = (ambient + diffuse);
	//frag_color determines the color of the pixel
	frag_color = vec4(result, 1.0f) * objectColor;
}