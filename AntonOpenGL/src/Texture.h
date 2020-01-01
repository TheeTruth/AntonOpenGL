#pragma once
#include <glew.h>
#include <string>
class Texture
{

private:
	unsigned int m_textureID;
public:
	Texture(const char* filePath, int format = GL_RGB, bool b_Flip = false);
	virtual ~Texture();
	void Bind();
};

