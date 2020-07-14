#pragma once

#include <string>
#include <fstream>
#include <vector>
#include <streambuf>

#include "XML/rapidxml.hpp"

using namespace rapidxml;


class LevelLoader {
private:
	std::vector<char> buffer;
public:
	LevelLoader();
	~LevelLoader();
	void LoadFile(const char* path);

};