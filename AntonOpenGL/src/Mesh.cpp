#include "Mesh.h"
#include <iostream>
//#include <vector>
#include "VertexBuffer.h"
#include "IndexBuffer.h"


Mesh::Mesh(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices)
{
	//std::vector<glm::vec3> model;
	for (int i = 0; i < numVertices; i++)
	{
		model.positions.push_back(*vertices[i].GetPos());
		model.texCoords.push_back(*vertices[i].GetTexCoord());
		model.normals.push_back(*vertices[i].GetNormal());
	}

	for (int i = 0; i < numIndices; i++)
	{
		model.indices.push_back(indices[i]);
	}
	
}

void Mesh::PrintPos()
{

}
