#pragma once

#include <iostream>
#include <Core/Application/Application.hpp>
#include "FirstScreen.hpp"

class MyApp : public Application 
{
public:
	void oninit() override { 
		fullonmaximize = true;
		std::cout << "oninit" << std::endl; 
	};
	void addscreens() override 
	{ 
		screens->add(new MyScreen());
		screens->set(0);
	

		std::cout << "addscreends" << std::endl; 
	};
	void onexit() override { std::cout << "onexit" << std::endl; };
};