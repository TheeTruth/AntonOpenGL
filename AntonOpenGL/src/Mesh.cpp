#include <glew.h>
#include <glfw3.h>

#include "Mesh.h"
#include <iostream>
//#include <vector>
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Renderer.h"


Mesh::Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices)
{
	m_numVertices = numVertices;
	//std::vector<glm::vec3> model;
	for (int i = 0; i < numVertices; i++)
	{
		m_model.positions.push_back(*vertices[i].GetPos());
		m_model.texCoords.push_back(*vertices[i].GetTexCoord());
		m_model.normals.push_back(*vertices[i].GetNormal());
	}

	for (int i = 0; i < numIndices; i++)
	{
		m_model.indices.push_back(indices[i]);
	}

	std::cout << "Sizeof(m_model.positions) " << sizeof(m_model.positions) * numVertices << std::endl;
	InitMesh();
}

void Mesh::InitMesh()
{
	m_numIndices = m_model.indices.size();

	GLCall(glGenVertexArrays(1, &m_vao));
	GLCall(glBindVertexArray(m_vao));
	// Position attribute
	VertexBuffer vbo_positions(&m_model.positions[0], sizeof(m_model.positions) * m_numVertices);
	GLCall(glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0));
	GLCall(glEnableVertexAttribArray(0));

	// texture coord attribute
	VertexBuffer vbo_texture(&m_model.texCoords[0], sizeof(m_model.texCoords) * m_numVertices);
	GLCall(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0));
	GLCall(glEnableVertexAttribArray(1));

	VertexBuffer vbo_normals(&m_model.normals[0], sizeof(m_model.normals) * m_numVertices);
	GLCall(glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, (void*)0));
	GLCall(glEnableVertexAttribArray(2));

	IndexBuffer indexBuffer(&m_model.indices[0], sizeof(m_model.indices));
}

void Mesh::Draw()
{
	GLCall(glBindVertexArray(m_vao));

	GLCall(glDrawElements(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, 0));
	//GLCall(glDrawElementsBaseVertex(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, 0, 0));

	GLCall(glBindVertexArray(0));
}
