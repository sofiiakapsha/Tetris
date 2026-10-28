#pragma once
#include <string>
#include <map>
#include "Game.h"

class Renderer {
private:
	static const std::string letters;
	std::map<GameState, std::string> hints;
public:
	Renderer();
	void draw(const Board& b, Block current);
	void drawScore(int score, int best);
	void drawState(GameState state);
};