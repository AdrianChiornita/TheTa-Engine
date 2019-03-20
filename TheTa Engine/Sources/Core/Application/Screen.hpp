#pragma once

constexpr size_t NO_SCREEN = 0xFFFFFFFF;

enum class ScreenState{
	NONE,
	RUNNING,
	EXIT,
	FORWARD,
	BACKWARD
};

class Application;

class Screen
{
	friend class ScreenList;
public:
	Screen() {};
	virtual ~Screen() {};

	virtual unsigned int nextindex() const = 0;
	virtual unsigned int previndex() const = 0;

	virtual void build() = 0;
	virtual void destroy() = 0;

	virtual void onstart() = 0;
	virtual void onstop() = 0;

	virtual void update() = 0;
	virtual void render() = 0;

	size_t getindex() const { return screenindex; };
	ScreenState getstate() const { return state; }

	void setstate(ScreenState state) { this->state = state; };
	void setmain(Application* app) { this->app = app; };

protected:
	Application *app = nullptr;
	ScreenState state = ScreenState::NONE;
	size_t screenindex = NO_SCREEN;
};
