#pragma once

#include "../Window/Window.hpp"
#include "../Managers/TimingManager.hpp"

#include <GL/glew.h>

class Engine
{
	public:
		static void init(WindowSettings settings, float maxFPS);
		static void exit();

		static bool isrunning() { return running; };
		static Window* getwindow() { return window; };
		static TimingManager* get_time_manager() { return time; };

	private:
		static Window* window;
		static TimingManager* time;
		static bool running;
};