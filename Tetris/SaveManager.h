#pragma once
#include <string>

class SaveManager {
public:
	SaveManager() = default;
	bool save(std::string file, std::string data);
	std::string load(std::string file);
	bool saveBestScore(int s);
	int loadBestScore();
};