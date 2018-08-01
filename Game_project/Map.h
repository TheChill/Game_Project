#pragma once
#include <string>

class Map {
private:
public:
	Map();
	static void load(std::string path, int size_x, int size_y);
	~Map();
};