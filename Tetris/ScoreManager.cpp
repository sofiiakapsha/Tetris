#include "ScoreManager.h"
#include <sstream>

void ScoreManager::addLines(int n) {
	static const int points[] = { 0, 100, 300, 500, 800 };
	int gotScore = points[n];
	score += gotScore;
	if (score > bestScore) bestScore = score;
}

int ScoreManager::getBest() { return bestScore; }

int ScoreManager::getScore() { return score; }

void ScoreManager::setBestScore(int s) {
	bestScore = s;
}

std::string ScoreManager::serialize() {
	return "SC:" + std::to_string(score) + ";" + std::to_string(bestScore);
}

void ScoreManager::deserialize(std::string data) {
	std::stringstream ss(data.substr(3));
	std::string part;

	std::getline(ss, part, ';'); 
	score = std::stoi(part);
	std::getline(ss, part, ';'); 
	bestScore = std::stoi(part);
}