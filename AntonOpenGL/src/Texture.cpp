#include "Texture.h"
#include "Renderer.h"
#include <iostream>
#include <glew.h>
#include <string>
#include "vendor/stb_image.h"


Texture::Texture(const char* filePath, int format, bool b_Flip)
{
	int width, height, nrChannels;

	//SET WRAP PARAMETERS
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// SET SAMPLING/FILTERING INTERPOLATION METHODS
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// SET MIPMAP SAMPLING METHODS
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


	std::cout << filePath << std::endl;
	stbi_set_flip_vertically_on_load(b_Flip);
	unsigned char* data = stbi_load(filePath, &width, &height, &nrChannels, 0);

	glGenTextures(1, &m_textureID);
	glBindTexture(GL_TEXTURE_2D, m_textureID);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

}


Texture::~Texture()
{
}

void Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, m_textureID);
}
