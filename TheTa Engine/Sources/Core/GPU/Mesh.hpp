#pragma once
#include <vector>
#include <GL/glew.h>

#include <sstream>
#include <string>

#include "Vertex.hpp"
#include "Material.hpp"
#include "Texture.hpp"
#include "GPUBuffers.hpp"
#include "Shader.hpp"

class Mesh
{
public:
		Mesh(std::string name, std::vector<Vertex> vertices, std::vector<GLuint> indices, std::vector<Texture> textures);
		void render(Shader *shader);

		std::string get_name() 
			{ return name; };

protected:
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;

private:
	GPUBuffers buffers;
	std::string name;
};