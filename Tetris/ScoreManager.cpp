#include "ScoreManager.h"
#include <sstream>
#include <stdexcept>

void ScoreManager::addLines(int n) {
	if (n <= 0 || n > 4) return;
	static const int points[] = { 0, 100, 300, 500, 800 };
	int gotScore = points[n];
	score += gotScore;
	if (score > bestScore) bestScore = score;
}

int ScoreManager::getBest() const { return bestScore; }

int ScoreManager::getScore() const { return score; }

void ScoreManager::setBestScore(int s) {
	bestScore = s;
}

std::string ScoreManager::serialize() const {
	return "SC:" + std::to_string(score) + ";" + std::to_string(bestScore);
}

void ScoreManager::deserialize(const std::string& data) {
	if (data.compare(0, 3, "SC:") != 0) throw std::runtime_error("bad score");

	std::stringstream ss(data.substr(3));
	std::string part;

	std::getline(ss, part, ';');
	int newScore = std::stoi(part);
	std::getline(ss, part, ';');
	int newBest = std::stoi(part);

	if (newScore < 0 || newBest < 0) throw std::runtime_error("bad score");

	score = newScore;
	bestScore = newBest;
}

void ScoreManager::reset() { score = 0; }