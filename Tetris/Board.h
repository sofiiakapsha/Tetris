#pragma once
#include "Block.h"

class Board {
private:
	std::vector<std::vector<int>> grid;
	static const int WIDTH = 10;
	static const int HEIGHT = 20;
public:
	Board() = default;

	bool canPlace(Block b);
	bool placeFigure(Block b);
	int clearLines();
	bool isLineFull(int row);
	void shiftDown(int row);
	std::string serialize();
	void deserialize(std::string data);
};