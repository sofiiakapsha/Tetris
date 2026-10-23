#pragma once
#include <string>
#include "Game.h"

class Renderer {
private:
	static const std::string letters;
public:
	Renderer();
	void draw(const Board& b, Block current);
	void drawScore(int score, int best);
	void drawState(GameState state);
};
