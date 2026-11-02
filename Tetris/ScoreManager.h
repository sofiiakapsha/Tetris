#pragma once
#include <string>

class ScoreManager {
private:
	int score;
	int bestScore;
public:
	ScoreManager(int score, int bestScore) : score(score), bestScore(bestScore) {};

	void addLines(int n);
	int getBest() const;
	void setBestScore(int s);
	std::string serialize() const;
	void deserialize(const std::string& data);
	int getScore() const;
	void reset();
};