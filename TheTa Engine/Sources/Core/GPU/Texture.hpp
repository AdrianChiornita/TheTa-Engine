#pragma once

#include <string>
#include <SOIL2/SOIL2.h>
#include <assimp/scene.h>

constexpr GLuint NO_TEXTURE = 0;

enum class TextureType {NONE, DIFFUSE, SPECULAR};

struct Texture {
	
	Texture(
		GLuint ID = NO_TEXTURE,
		TextureType type = TextureType::NONE,
		aiString path = {}
	) : ID(ID),
		type(type),
		path(path) {};

	GLuint ID;
	aiString path;
	TextureType type;
};

static GLuint create_texture(std::string path)
{
	GLuint ID = NO_TEXTURE;
	glGenTextures(1, &ID);

	ID = SOIL_load_OGL_texture(
		path.c_str(), 
		SOIL_LOAD_AUTO, 
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_MULTIPLY_ALPHA 
	);

	glBindTexture(GL_TEXTURE_2D, ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, NO_TEXTURE);

	return ID;
}