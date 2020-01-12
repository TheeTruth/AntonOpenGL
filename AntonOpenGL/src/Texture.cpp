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
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT));

	// SET SAMPLING/FILTERING INTERPOLATION METHODS
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));

	// SET MIPMAP SAMPLING METHODS
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));


	std::cout << filePath << std::endl;
	stbi_set_flip_vertically_on_load(b_Flip);
	unsigned char* data = stbi_load(filePath, &width, &height, &nrChannels, 0);

	GLCall(glGenTextures(1, &m_textureID));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_textureID));

	if (data)
	{
		GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data));
		GLCall(glGenerateMipmap(GL_TEXTURE_2D));
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
	GLCall(glBindTexture(GL_TEXTURE_2D, m_textureID));
}
