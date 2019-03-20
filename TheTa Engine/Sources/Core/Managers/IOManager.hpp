#pragma once

#include <fstream>
#include <filesystem>
#include <string>
#include <vector>


// add input and output functionalities

class IOManager
{
	static bool read(std::string path, std::string &buffer);
	static bool read(std::string path, std::vector<unsigned char> &buffer);
};