#include "GPUBuffers.hpp"

GPUBuffers::GPUBuffers()
{
	VAO = VBO = EBO = NO_BUFFER;
}

void GPUBuffers::CreateBuffers()
{
	glGenVertexArrays	(1, &VAO);
	glGenBuffers		(1, &VBO);
	glGenBuffers		(1, &EBO);
}

void GPUBuffers::ReleaseMemory()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers		(1, &VBO);
	glDeleteBuffers		(1, &EBO);
}

void GPUBuffers::upload(const std::vector<Vertex>& vertices, const std::vector<GLuint>& indices)
{
	if(VAO != NO_BUFFER || VBO != NO_BUFFER || EBO != NO_BUFFER) 
		this->ReleaseMemory();
	
	this->CreateBuffers();

	glBindVertexArray(this->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), &indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *) 0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, sizeof(Vertex), (GLvoid *) offsetof(Vertex, normal));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid *) offsetof(Vertex, texcoords));

	glBindVertexArray(NO_BUFFER);
}

GLuint GPUBuffers::get_vao()
{
	return this->VAO;
}
