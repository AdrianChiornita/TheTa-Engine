#include "IOManager.hpp"

bool IOManager::read(std::string path, std::string &buffer)
{
	std::ifstream file(path, std::ios::binary);

	if (file.fail()) return false;
	
	unsigned int size = 0;
	
	file.seekg(0, std::ios::end);
	size = (unsigned int) file.tellg();
	file.seekg(0, std::ios::beg);
	size -= (unsigned int) file.tellg();

	buffer.resize(size);
	file.read((char *) &(buffer[0]), size);
	file.close();

	return true;
}

bool IOManager::read(std::string path, std::vector<unsigned char> &buffer)
{
	std::ifstream file(path, std::ios::binary);

	if (file.fail()) return false;
	
	unsigned int size;
	
	file.seekg(0, std::ios::end);
	size = (unsigned int) file.tellg();
	file.seekg(0, std::ios::beg);
	size -= (unsigned int) file.tellg();

	buffer.resize(size);
	file.read((char *) &(buffer[0]), size);
	file.close();

	return true;
}