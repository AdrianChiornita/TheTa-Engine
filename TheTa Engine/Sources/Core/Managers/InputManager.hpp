#pragma once

#include <SDL.h>
#include <glm/glm.hpp>

class InputKeyboard
{
public:
	InputKeyboard() { init(); };
	~InputKeyboard() {};

	void update();

	bool is_key_pressed(const SDL_Scancode key) const;
	bool is_key_triggered(const SDL_Scancode key) const;
	bool is_key_released(const SDL_Scancode key) const;

private:
	void init();

	Uint8 prevkeys[SDL_NUM_SCANCODES];
	Uint8 currkeys[SDL_NUM_SCANCODES];
};

class InputMouse
{
public:
	InputMouse() { init(); };
	~InputMouse() {};

	void update();

	Sint32 get_wheel_x() const;
	Sint32 get_wheel_y() const;
	glm::ivec2 get_position() const;
	glm::ivec2 get_relposition() const;

	bool is_button_pressed(const Uint32 button) const;
	bool is_button_triggered(const Uint32 button) const;
	bool is_button_released(const Uint32 button) const;

	void set_wheel(const SDL_Event event);

private:
	void init();

	glm::ivec2 currcoords;
	Uint32 currstate;

	glm::ivec2 prevcoords;
	Uint32 prevstate;

	Sint32 wheel_x, wheel_y;
};


