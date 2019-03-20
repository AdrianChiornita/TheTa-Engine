#pragma once
#include <GLM/glm.hpp>

typedef glm::vec3 Position;
typedef glm::vec3 Normal;
typedef glm::vec4 Color;
typedef glm::vec2 Tex2D;

struct Vertex
{
	Vertex(
		Position position			= glm::vec3(0.0f),
		Normal normal				= glm::vec3(0.0f),
		Tex2D texcoords				= glm::vec2(0.0f)
	) : position(position),
		normal(normal),
		texcoords(texcoords) {};

	Position position;
	Normal normal;
	Tex2D texcoords;
};