#include "Application.hpp"

Application::Application()
{
	screens = std::make_unique<ScreenList>(this);
	keyboard = new InputKeyboard();
	mouse = new InputMouse();
}

Application::~Application()
{
}

void Application::run()
{
	if(!init()) return;

	running = true;
	while (running)
	{
		Engine::get_time_manager()->begin();
		SDL_Event event;
		if (SDL_PollEvent(&event)) onevent(event);

		keyboard->update();
		mouse->update();

		update();

		if (running)
		{
			render();
			delta = Engine::get_time_manager()->end();
			
			window->swapbuffers();
		}
	}

	exit();
}

void Application::exit()
{
	currentscreen->onstop();
	if (screens)
	{
		screens->destroy();
		screens.reset();
	}
	running = false;

	Engine::exit();
}

void Application::onevent(SDL_Event &event)
{
	switch (event.type) {
	case SDL_WINDOWEVENT:
		switch (event.window.event) {
		case SDL_WINDOWEVENT_CLOSE:
			exit();
			break;
		case SDL_WINDOWEVENT_MINIMIZED:
			window->minimize();
			break;
		case SDL_WINDOWEVENT_MAXIMIZED:
			if (fullonmaximize) window->full();
			else window->maximize();
			break;
		case SDL_WINDOWEVENT_HIDDEN:
			window->hide();
			break;
		case SDL_WINDOWEVENT_SHOWN:
			window->show();
			break;
		case SDL_WINDOWEVENT_SIZE_CHANGED:
			window->windowed();
			break;
		default:
			break;
		}
		break;
	case SDL_QUIT:
		exit();
		break;
	default:
		break;
	}
}

void Application::update()
{
	if (currentscreen)
		switch (currentscreen->getstate())
		{
		case ScreenState::RUNNING:
			currentscreen->update();
			break;
		case ScreenState::FORWARD:
			currentscreen->onstop();
			currentscreen = screens->forward();
			if (currentscreen)
			{
				currentscreen->setstate(ScreenState::RUNNING);
				currentscreen->onstart();
			}
			else
				ExceptionManager::fatalError("Failed changing screen forward" + currentscreen->getindex());
			break;
		case ScreenState::BACKWARD:
			currentscreen->onstop();
			currentscreen = screens->backward();
			if (currentscreen)
			{
				currentscreen->setstate(ScreenState::RUNNING);
				currentscreen->onstart();
			}
			else
				ExceptionManager::fatalError("Failed changing screen backward" + currentscreen->getindex());
			break;
		case ScreenState::EXIT:
			exit();
			break;
		default:
			break;
		}
	else
		exit();
}

void Application::render()
{
	glViewport(0, 0, window->getresolution().x, window->getresolution().y);
	if (currentscreen && currentscreen->getstate() == ScreenState::RUNNING)
		currentscreen->render();
}

bool Application::init()
{
	if (!Engine::isrunning()) return false;

	window = Engine::getwindow();

	glViewport(0, 0, window->getresolution().x, window->getresolution().y);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	oninit();
	addscreens();

	currentscreen = screens->get();
	currentscreen->onstart();
	currentscreen->setstate(ScreenState::RUNNING);
	return true;
}
