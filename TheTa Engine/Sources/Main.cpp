#include <iostream>
#include <windows.h>
#include <string>

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <GL/glew.h>

#include <Core/Engine/Engine.hpp>
#include <Graphics Projects/Testing TheTa/FirstApp.hpp>

int main(int argc, char *argv[])
{
	WindowSettings settings = WindowSettings();
	
	Engine::init(settings, 60.0f);

	MyApp app;
	app.run();

	return 0;
}