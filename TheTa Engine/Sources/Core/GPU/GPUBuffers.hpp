#pragma once

#include <vector>

#include <GLM/glm.hpp>
#include <GL/glew.h>

#include "Vertex.hpp"

constexpr GLuint NO_BUFFER = 0;

class GPUBuffers
{
	public:
		GPUBuffers();

		void CreateBuffers();
		void ReleaseMemory();

		void upload(
			const std::vector<Vertex> &vertices,
			const std::vector<GLuint> &indices
		);

		GLuint get_vao();

	private:
		GLuint VAO;
		GLuint VBO;
		GLuint EBO;
};