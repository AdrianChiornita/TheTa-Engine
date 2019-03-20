#pragma once

#include <GLM/glm.hpp>

struct Perspective
{
	Perspective(
		float fov = 60.0f,
		float aratio = 1280.0f / 720.0f,
		float znear = 0.1f,
		float zfar = 100.0f
	) : fov(fov),
		aratio(aratio),
		znear(znear),
		zfar(zfar) {};

	float fov;
	float aratio;
	float znear;
	float zfar;
};

struct Orthographic
{
	Orthographic(
		float left = 0.0f,
		float right = 1280.0f,
		float bottom = 0.0f,
		float top = 720.0f
	) : left(left),
		right(right),
		bottom(bottom),
		top(top) {};

	float left;
	float right;
	float bottom;
	float top;
};

union Projection
{
	Perspective  *perspective;
	Orthographic *ortho;
};