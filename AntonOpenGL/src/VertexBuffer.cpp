#include "VertexBuffer.h"
#include "Renderer.h"
#include <glew.h>

VertexBuffer::VertexBuffer(const void* data,unsigned int size)
{
	std::cout << "\nVBO" << std::endl;
	std::cout << "sizeof(data): " << sizeof(data) << std::endl;
	GLCall(glGenBuffers(1, &m_Id));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_Id));
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_Id));
}

void VertexBuffer::Bind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_Id));
}

void VertexBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
