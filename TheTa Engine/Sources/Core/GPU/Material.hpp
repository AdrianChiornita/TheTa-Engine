#pragma once
#include <glm/glm.hpp>

static const unsigned int INVALID_MATERIAL = 0xFFFFFFFF;

struct Material
{
	Material(
		glm::vec4 ambient	= glm::vec4(0.0f),
		glm::vec4 diffuse	= glm::vec4(0.0f),
		glm::vec4 specular	= glm::vec4(0.0f),
		glm::vec4 emissive	= glm::vec4(0.0f),
		float shininess		= 0.0f
	) : ambient(ambient),
		diffuse(diffuse),
		specular(specular),
		emissive(emissive),
		shininess(shininess) 
	{

	};

	glm::vec4 ambient;
	glm::vec4 diffuse;
	glm::vec4 specular;
	glm::vec4 emissive;
	float shininess;
};