#include "Engine.hpp"

Window* Engine::window = nullptr;
TimingManager* Engine::time = nullptr;
bool Engine::running = false;

void Engine::init(WindowSettings settings, float maxFPS)
{
	// SDL initialization
	SDL_Init(SDL_INIT_EVERYTHING);

	/*0
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);

	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	*/
	//SDL_SetRelativeMouseMode(SDL_TRUE);

	// Create window for the app
	window = new Window(settings);

	// Create timing manager for frame time and FPS
	time   = new TimingManager();
	time->init();

	// GLEW initialization
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
		ExceptionManager::fatalError("GLEW not initialized");

	running = true;
}

void Engine::exit()
{
	running = false;
	window->close();

	// delete window and quit SDL
	window->~Window();
	SDL_Quit();
}
