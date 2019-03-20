#pragma once

#include <string>
#include <iostream>

#include <SDL.h>

class ExceptionManager
{
public:
	static void fatalError(std::string msg);
	static void exception(std::string msg);
};