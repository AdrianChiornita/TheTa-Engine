#include "Window.hpp"

Window::Window(WindowSettings settings) : settings(settings)
{
	window = nullptr;
	Uint32 flags = SDL_WINDOW_OPENGL;

	if (settings.visible)	flags |= SDL_WINDOW_SHOWN;
	else					flags |= SDL_WINDOW_HIDDEN;
	if (settings.full)		flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
	if (settings.resizable) flags |= SDL_WINDOW_RESIZABLE;
	if (settings.borderless)flags |= SDL_WINDOW_BORDERLESS;

	if (settings.centered)
	{
		window = SDL_CreateWindow(
			settings.name.c_str(),
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED,
			settings.resolution.x,
			settings.resolution.y,
			flags
		);
		settings.position = 
			glm::ivec2(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	}
	else
		window = SDL_CreateWindow(
			settings.name.c_str(),
			settings.position.x,
			settings.position.y,
			settings.resolution.x,
			settings.resolution.y,
			flags
		);

	if (window == nullptr)
		ExceptionManager::fatalError("Window not created");
	
	context = SDL_GL_CreateContext(window);
	if (context == nullptr)
		ExceptionManager::fatalError("OpenGL context not created");
}

Window::~Window()
{
	SDL_GL_DeleteContext(SDL_GL_GetCurrentContext());
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Window::swapbuffers() const
{
	SDL_GL_SwapWindow(window);
}

void Window::show()
{
	settings.visible = true;
	SDL_ShowWindow(window);
}

void Window::hide()
{
	settings.visible = false;
	SDL_HideWindow(window);
}

void Window::close()
{
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Window::maximize()
{
	SDL_MaximizeWindow(window);
	SDL_GetWindowSize(
		window, 
		&settings.resolution.x,
		&settings.resolution.y
	);
}

void Window::minimize()
{
	SDL_MinimizeWindow(window);
}

void Window::full()
{
	if (settings.resizable)
	{
		settings.full = true;
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
	}	
}

void Window::windowed()
{
	if (settings.resizable)
	{
		settings.full = false;
		SDL_GetWindowSize(
			window,
			&settings.resolution.x,
			&settings.resolution.y
		);
	}
}

void Window::setposition(glm::ivec2 position)
{
	settings.position = position;
	SDL_SetWindowPosition(window, settings.position.x, settings.position.y);
}

void Window::setbordered()
{
	settings.borderless = !settings.borderless;
	SDL_SetWindowBordered(window, (SDL_bool)settings.borderless);
}

void Window::setresizable()
{
	settings.resizable = !settings.resizable;
	SDL_SetWindowResizable(window, (SDL_bool)settings.resizable);
}

void Window::center()
{
	settings.position = glm::ivec2(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
}

void Window::setvsync(bool state)
{
	SDL_GL_SetSwapInterval(state);
}

bool Window::togglevsync()
{
	settings.vsync = !settings.vsync;
	SDL_GL_SetSwapInterval(!settings.vsync);
	return settings.vsync;
}

void Window::setresolution(int width, int height)
{
	settings.resolution = glm::ivec2(width, height);
	SDL_SetWindowSize(
		window,
		settings.resolution.x,
		settings.resolution.y
	);
}

glm::ivec2 Window::getresolution() const
{
	return settings.resolution;
}
