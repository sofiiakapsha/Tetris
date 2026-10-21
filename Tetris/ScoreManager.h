#pragma once
#include <string>


class ScoreManager {
private:
	int score;
	int bestScore;
public:
	ScoreManager(int score, int bestScore) : score(score), bestScore(bestScore) {};

	void addLines(int n);
	int getBest();
	void setBestScore(int s);
	std::string serialize();
	void deserialize(std::string data);
	int getScore();
};
