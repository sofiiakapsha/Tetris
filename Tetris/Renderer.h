#pragma once
#include <string>
#include "Board.h"
#include "Block.h"
#include "State.h"

class Renderer {
private:
	static const std::string letters;
public:
	Renderer();
	void draw(const Board& b, const Block& current);
	void drawScore(int score, int best);
	void drawState(const State& state);
};