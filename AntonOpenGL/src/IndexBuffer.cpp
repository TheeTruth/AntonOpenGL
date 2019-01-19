#include "IndexBuffer.h"
#include "Renderer.h"
#include <iostream>
#include <glew.h>

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
	: m_Count(count)
{
	std::cout << "\nIBO" << std::endl;
	std::cout << "Data: " << data[1] << std::endl;
	std::cout << "Count: " << count << std::endl;
	GLCall(glGenBuffers(1, &m_Id));
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id));
	GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_Id));
}

void IndexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_Id));
}

void IndexBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

