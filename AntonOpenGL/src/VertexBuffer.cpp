#include "VertexBuffer.h"
#include "Renderer.h"
#include <GlEW/glew.h>

VertexBuffer::VertexBuffer(const void* data,unsigned int size)
{
	GLCall(glGenBuffers(1, &m_Id));
	glBindBuffer(GL_ARRAY_BUFFER, m_Id);
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_Id);
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_Id);
}

void VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
