#include "Mesh.hpp"

Mesh::Mesh(std::string name, std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures)
{
	this->name = name;
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;

	buffers.upload(this->vertices, this->indices);
}

void Mesh::render(Shader *shader)
{
	GLuint diffuseNr = 1, specularNr = 1;

	for (GLuint i = 0; i < textures.size(); ++i)
	{
		glActiveTexture(GL_TEXTURE0 + i);

		std::stringstream ss;
		std::string number;

		if (this->textures[i].type == TextureType::DIFFUSE)
		{
			ss << diffuseNr++;
		}
		else if (this->textures[i].type == TextureType::SPECULAR)
		{
			ss << specularNr++;
		}

		number = ss.str();
		glUniform1i(shader->get_uniform_location(("sample" + number).c_str()), i);
		glBindTexture(GL_TEXTURE_2D, this->textures[i].ID);
	}

	glUniform1f(shader->get_uniform_location( "material.shininess"), 16.0f);

	glBindVertexArray(this->buffers.get_vao());
	glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);


	for (GLuint i = 0; i < this->textures.size(); ++i)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, NO_TEXTURE);
	}
}
