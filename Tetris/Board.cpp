#include "Board.h"
#include <sstream>
#include <stdexcept>
#include <string>

bool Board::canPlace(const Block& b) const {
	for (const auto& cell : b.calculatePlaces()) {
		int px = cell[0];
		int py = cell[1];

		if (px < 0 || px >= width || py < 0 || py >= height) return false;
		if (grid[py][px] != 0) return false;
	}
	return true;
}

bool Board::placeFigure(const Block& b) {
	if (!canPlace(b)) return false;

	for (const auto& cell : b.calculatePlaces()) {
		grid[cell[1]][cell[0]] = b.getType() + 1;
	}
	return true;
}

bool Board::isLineFull(int row) const {
	if (row < 0 || row >= height) return false;
	for (int c : grid[row]) {
		if (c == 0) return false;
	}
	return true;
}

void Board::shiftDown(int row) {
	for (int r = row; r > 0; --r) {
		grid[r] = grid[r - 1];
	}
	grid[0].assign(width, 0);
}

std::string Board::serialize() const {
	int h = grid.size();
	int w = grid[0].size();
	std::string cells;
	for (const auto& row : grid) {
		for (int c : row) {
			cells += std::to_string(c);
		}
	}

	return "BO:" + std::to_string(h) + ";" + std::to_string(w) + ";" + cells;
}

void Board::deserialize(const std::string& data) {
	if (data.compare(0, 3, "BO:") != 0) throw std::runtime_error("bad board");

	std::stringstream ss(data.substr(3));
	std::string part;

	std::getline(ss, part, ';');
	int h = std::stoi(part);
	std::getline(ss, part, ';');
	int w = std::stoi(part);
	std::string cells;
	std::getline(ss, cells, ';');

	if (h != height || w != width || cells.size() != static_cast<size_t>(h) * w) {
		throw std::runtime_error("bad board");
	}

	std::vector<std::vector<int>> newGrid(h, std::vector<int>(w, 0));
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			int v = cells[i * w + j] - '0';
			if (v < 0 || v > 7) throw std::runtime_error("bad board cell");
			newGrid[i][j] = v;
		}
	}
	grid = std::move(newGrid);
}

int Board::clearLines() {
	int count = 0;
	int row = height - 1;

	while (row >= 0) {
		if (isLineFull(row)) {
			shiftDown(row);
			count++;
		}
		else {
			row--;
		}
	}
	return count;
}

void Board::addedFeature() {
	int line = (int)grid.size() - 1;
	int row = (int)grid[line].size();

	for (int j = 0; j < row; ++j) {
		grid[line][j] = 1;
	}
}

int Board::getCell(int x, int y) const {
	if (x < 0 || x >= width || y < 0 || y >= height) return 0;
	return grid[y][x];
}

int Board::getWidth() const { return width; }

int Board::getHeight() const { return height; }