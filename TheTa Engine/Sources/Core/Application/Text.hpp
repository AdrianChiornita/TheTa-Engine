#pragma once

#include <vector>
#include <GLM/glm.hpp>

class  Text
{
public:
	 Text(std::string path);
	~ Text();

	void print(std::string text, int x, int y, int size);
	void clean();

private:
	std::vector<glm::vec2> vertices;
	std::vector<glm::vec2> uvs;
};
