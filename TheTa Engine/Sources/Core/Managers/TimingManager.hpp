#pragma once

#include <SDL.h>


// add calculation of FPS
// create timestamp manager

class TimingManager
{
	public:
		TimingManager();

		void init();
		void begin();
		float end();

		float getframetime() { return frame; };

	private:

		unsigned int start;
		float frame;
};