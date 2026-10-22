#include "SaveManager.h"
#include <iostream>
#include <fstream>
#include <sstream>

bool SaveManager::save(std::string file, std::string data) {
	std::ofstream outputFile(file);
    if (outputFile.is_open()) {

        outputFile << data;

        outputFile.close();
        return true;
    }

    return false;
}

std::string SaveManager::load(std::string file) {
    std::ifstream in(file);
    if (!in.is_open()) return "";

    std::stringstream buffer;
    buffer << in.rdbuf();
    return buffer.str();
}

bool SaveManager::saveBestScore(int s) {
    std::ofstream outputFile("best_score.txt");
    if (outputFile.is_open()) {

        outputFile << s;

        outputFile.close();
        return true;
    }

    return false;
}

int SaveManager::loadBestScore() {
    std::ifstream in("best_score.txt");
    int score = 0;
    if (in >> score) return score;
    return 0;
}
