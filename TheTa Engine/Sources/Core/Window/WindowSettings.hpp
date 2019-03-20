#pragma once

#include <string>
#include <GLM/glm.hpp>


struct WindowSettings
{
	WindowSettings(
		std::string name = "TheTa Engine Application",
		glm::ivec2 resolution	= glm::ivec2(1280, 720),
		glm::ivec2 position		= glm::ivec2(0),
		glm::ivec2 cursor		= glm::ivec2(1280, 720) / 2,
		float aratio = 1280.0f / 720.0f,
		bool resizable = true,
		bool borderless = false,
		bool hdpi = false,
		bool visible = true,
		bool full = false,
		bool centered = true,
		bool hideq = false,
		bool vsync = true
	) : name(name),
		resolution(resolution),
		position(position),
		cursor(cursor),
		aratio(aratio),
		resizable(resizable),
		borderless(borderless),
		hdpi(hdpi),
		visible(visible),
		full(full),
		centered(centered),
		hideq(hideq),
		vsync(vsync) {};

	std::string name;
	glm::ivec2 resolution;
	glm::ivec2 position;
	glm::ivec2 cursor;
	float aratio;
	bool resizable;
	bool borderless;
	bool hdpi;
	bool visible;
	bool full;
	bool centered;
	bool hideq;
	bool vsync;
};
