#include "ExceptionMannager.hpp"

void ExceptionManager::fatalError(std::string msg)
{
	std::cout << msg << std::endl;
	
	SDL_Quit();
	exit(EXIT_FAILURE);
}

void ExceptionManager::exception(std::string msg)
{
	std::cout << msg << std::endl;
}
