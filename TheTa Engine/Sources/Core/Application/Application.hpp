#pragma once

#include <memory>

#include "../Engine/Engine.hpp"
#include "../Managers/InputManager.hpp"
#include "ScreenList.hpp"

class Screen;
class ScreenList;

class Application
{
public:
	Application();
	virtual ~Application();

	void run();
	void exit();

	virtual void oninit() = 0;
	virtual void addscreens() = 0;
	virtual void onexit() = 0;

	void onevent(SDL_Event &event);

	const Window* get_window() const { return window; };
	const InputKeyboard* get_keyboard() const { return keyboard; };
	const InputMouse* get_mouse() const { return mouse; };

	float delta = 0.0f;

protected:
	Screen* currentscreen = nullptr;
	std::unique_ptr<ScreenList> screens = nullptr;

	bool fullonmaximize = false;
	Window* window = nullptr;
	
	InputKeyboard* keyboard = nullptr;
	InputMouse* mouse = nullptr;
	
private:
	virtual void update();
	virtual void render();

	bool init();

	bool running = false;
};