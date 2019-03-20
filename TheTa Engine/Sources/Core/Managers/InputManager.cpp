#include "InputManager.hpp"

void InputKeyboard::init()
{
	SDL_memset(prevkeys, 0, sizeof(Uint8) * SDL_NUM_SCANCODES);
	SDL_memcpy(currkeys, SDL_GetKeyboardState(nullptr), sizeof(Uint8) * SDL_NUM_SCANCODES);
}

void InputKeyboard::update()
{
	SDL_memcpy(prevkeys, currkeys, sizeof(Uint8) * SDL_NUM_SCANCODES);
	SDL_memcpy(currkeys, SDL_GetKeyboardState(nullptr), sizeof(Uint8) * SDL_NUM_SCANCODES);
}

bool InputKeyboard::is_key_pressed(const SDL_Scancode key) const
{
	return currkeys[key];
}

bool InputKeyboard::is_key_triggered(const SDL_Scancode key) const
{
	return (currkeys[key] && !prevkeys[key]);
}

bool InputKeyboard::is_key_released(const SDL_Scancode key) const
{
	return (!currkeys[key] && prevkeys[key]);
}

void InputMouse::init()
{
	prevcoords.x = prevcoords.y = 0;
	prevstate = 0;
	currstate = SDL_GetMouseState(&currcoords.x, &currcoords.y);
	wheel_x = wheel_y = 0;
}


void InputMouse::update()
{
	prevcoords = currcoords;
	prevstate = currstate;

	currstate = SDL_GetMouseState(&currcoords.x, &currcoords.y);
	wheel_x = wheel_y = 0;
}

Sint32 InputMouse::get_wheel_x() const
{
	return wheel_x;
}

Sint32 InputMouse::get_wheel_y() const
{
	return wheel_y;
}

glm::ivec2 InputMouse::get_position() const
{
	return currcoords;
}

glm::ivec2 InputMouse::get_relposition() const
{
	return currcoords - prevcoords;
}

bool InputMouse::is_button_pressed(const Uint32 button) const
{
	return (SDL_BUTTON(button) & currstate);
}

bool InputMouse::is_button_triggered(const Uint32 button) const
{
	return (SDL_BUTTON(button) & currstate) && !(SDL_BUTTON(button) & prevstate);
}

bool InputMouse::is_button_released(const Uint32 button) const
{
	return !(SDL_BUTTON(button) & currstate) && (SDL_BUTTON(button) & prevstate);
}

void InputMouse::set_wheel(const SDL_Event event)
{
	if (event.type == SDL_MOUSEWHEEL)
	{
		wheel_x = event.wheel.x;
		wheel_y = event.wheel.y;
	}
}
