#pragma once

#include "WindowSettings.hpp"
#include "../Managers/ExceptionMannager.hpp"

class Window
{
	public:
		Window(WindowSettings settings);
		~Window();

		void swapbuffers() const;
		
		void show();
		void hide();
		void close();

		void maximize();
		void minimize();
		void full();
		void windowed();

		void setposition(glm::ivec2 position);

		void setbordered();
		void setresizable();
		void center();

		void setvsync(bool state);
		bool togglevsync();

		void setresolution(int width, int height);
		glm::ivec2 getresolution() const;

	private:
		SDL_Window* window;
		SDL_GLContext context;
		WindowSettings settings;
};