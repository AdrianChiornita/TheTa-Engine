#include "ScreenList.hpp"
#include "Application.hpp"

ScreenList::ScreenList(Application * app) : app(app)
{
	//
}

ScreenList::~ScreenList()
{
	destroy();
}

Screen * ScreenList::forward()
{
	Screen* current = get();
	if (current->nextindex() != NO_SCREEN)
		set(current->nextindex());
	return get();
}

Screen * ScreenList::backward()
{
	Screen* current = get();
	if (current->previndex() != NO_SCREEN)
		set(current->previndex());
	return get();
}

void ScreenList::set(size_t index)
{
	current = index;
}

void ScreenList::add(Screen * screen)
{
	screen->screenindex = list.size();
	list.push_back(screen);

	screen->build();
	screen->setmain(app);
}

void ScreenList::destroy()
{
	for (auto screen : list)
		screen->destroy();

	list.resize(0);
	current = NO_SCREEN;
}

Screen * ScreenList::get()
{
	if (current == NO_SCREEN) return nullptr;
	return list[current];
}
