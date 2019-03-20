#include "TimingManager.hpp"

TimingManager::TimingManager() {}

void TimingManager::init() {}

void TimingManager::begin()
{
	start = SDL_GetTicks();
}

float TimingManager::end()
{
	return (float) (SDL_GetTicks() - start) / 1000.0f;
}
