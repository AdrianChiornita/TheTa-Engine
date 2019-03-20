#pragma once

#include <vector>

#include "Screen.hpp"

class Application;

class ScreenList
{
public:
	ScreenList(Application *app);
	~ScreenList();

	Screen* forward();
	Screen* backward();

	void set(size_t index);
	void add(Screen* screen);

	void destroy();

	Screen* get();

private:
	Application* app = nullptr;
	std::vector<Screen*> list;
	size_t current = NO_SCREEN;
};