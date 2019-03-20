#include "Shader.hpp"

Shader::Shader(std::string name)
{
	ID = NO_SHADER_ID;
	this->name = name;
	files.reserve(MAX_SHADERS);
}

Shader::~Shader()
{
	glDeleteProgram(ID);
}

std::string Shader::get_name() const
{
	return name;
}

GLuint Shader::get_program() const
{
	return ID;
}

GLint Shader::get_uniform_location(std::string name) const
{
	return glGetUniformLocation(ID, name.c_str());
}

void Shader::use() const
{
	if (ID)
		glUseProgram(ID);
}

GLuint Shader::reload()
{
	if (ID) 
	{
		glDeleteProgram(ID);
		ID = NO_SHADER_ID;
	}

	return setup();
}

void Shader::add(const std::string &file, GLenum type)
{
	GLSLFile shader;

	shader.file = file;
	shader.type = type;
	files.push_back(shader);
}

GLuint Shader::setup()
{
	std::vector<GLuint> shaders;

	for (GLSLFile shader : files) {
		GLuint ID = Shader::create(shader.file, shader.type);
		if (ID)
			shaders.push_back(ID);
		else
			return NO_SHADER_ID;
	}

	if (shaders.size()) {
		ID = Shader::generate(shaders);

		if (ID)
		{
			glUseProgram(ID);
			return ID;
		}
	}

	return NO_SHADER_ID;
}

void Shader::clear()
{
	files.clear();
}

GLuint Shader::create(const std::string &path, GLenum type)
{
	std::string code;
	std::ifstream file(path.c_str(), std::ios::in);

	if (!file.good())
		ExceptionManager::fatalError("[ERROR]:: Shader file not read:\n" + path);
	
	file.seekg(0, std::ios::end);
	code.resize((unsigned int) file.tellg());
	file.seekg(0, std::ios::beg);
	file.read(&code[0], code.size());
	file.close();

	GLuint shader = NO_SHADER_ID;
	shader = glCreateShader(type);
	if (shader == NO_SHADER_ID)
	{
		ExceptionManager::fatalError("[ERROR]:: Shader file not created:\n" + path);
		return NO_SHADER_ID;
	}

	const char *ptr = code.c_str();
	const int size = (int) code.size();

	glShaderSource(shader, 1, &ptr, &size);
	glCompileShader(shader);

	switch (type)
	{
	case GL_VERTEX_SHADER:
		error(shader, "VERTEX");
		break;
	case GL_TESS_CONTROL_SHADER:
		error(shader, "TESS CONTROL");
		break;
	case GL_TESS_EVALUATION_SHADER:
		error(shader, "TESS EVAL");
		break;
	case GL_GEOMETRY_SHADER:
		error(shader, "GEOMETRY");
		break;
	case GL_FRAGMENT_SHADER:
		error(shader, "FRAGMENT");
		break;
	case GL_COMPUTE_SHADER:
		error(shader, "COMPUTE");
		break;
	default:
		break;
	}

	return shader;
}

unsigned int Shader::generate(const std::vector<GLuint> &shaders)
{
	GLuint program = glCreateProgram();

	for (auto shader : shaders)
		glAttachShader(program, shader);

	glLinkProgram(program);

	error(program, "PROGRAM");

	for (auto shader : shaders)
		glDeleteShader(shader);

	return program;
}

void Shader::error(GLuint shader, std::string type)
{
	GLint success;
	GLchar log[GL_INFO_LOG_LENGTH];

	if (type != "program")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, GL_INFO_LOG_LENGTH, NULL, log);
			ExceptionManager::fatalError(
				"[ERROR]:: SHADER COMPILATION of: " +
				type +
				"\n" +
				log  );
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, GL_INFO_LOG_LENGTH, NULL, log);
			ExceptionManager::fatalError(
				"[ERROR]:: PROGRAM LINKING of: " +
				type +
				"\n" +
				log  );
		}
	}
}
