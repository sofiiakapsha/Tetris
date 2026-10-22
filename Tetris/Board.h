#pragma once
#include "Block.h"

class Board {
private:
	std::vector<std::vector<int>> grid;
	static const int width = 10;
	static const int height = 20;
public:
	Board() : grid(height, std::vector<int>(width, 0)) {}

	bool canPlace(Block b);
	bool placeFigure(Block b);
	int clearLines();
	void addedFeature();
	bool isLineFull(int row);
	void shiftDown(int row);
	int getCell(int x, int y) const;
	int getWidth() const;
	int getHeight() const;
	std::string serialize();
	void deserialize(const std::string& data);
};