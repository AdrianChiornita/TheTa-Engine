#pragma once

#include "../Managers/ExceptionMannager.hpp"

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include <GL/glew.h>
#include <GLM/glm.hpp>

constexpr GLuint NO_SHADER_ID = 0;
constexpr unsigned int MAX_SHADERS = 6;

class Shader
{
	public:
		Shader(std::string name);
		~Shader();

		std::string get_name() const;
		GLuint get_program() const;
		GLint get_uniform_location(std::string name) const;

		void use() const;
		GLuint reload();

		void add(const std::string &path, GLenum type);
		void clear();
		GLuint setup();

	private:
		GLuint create(const std::string &path, GLenum type);
		GLuint generate(const std::vector<GLuint> &shaders);
		void error(GLuint shader, std::string type);

	private:
		struct GLSLFile
		{
			std::string file;
			GLenum type;
		};

		GLuint ID;
		std::string name;
		std::vector<GLSLFile> files;
};
