#include "Block.h"
#include <sstream>
#include <stdexcept>

std::string Block::getColor() const {
	return color;
}

int Block::getRotation() const {
	return rotation;
}

int Block::getType() const {
	return type;
}

void Block::rotate() {
	rotation = (rotation + 1) % 4;
	int n = shape.size();
	std::vector<std::vector<int>> rotated(n, std::vector<int>(n));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			rotated[j][n - 1 - i] = shape[i][j];
		}
	}
	shape = rotated;
}

void Block::move(int dx, int dy) {
	x += dx;
	y += dy;
}

std::string Block::serialize() const {
	int n = shape.size();
	std::string cells;
	for (const auto& row : shape) {
		for (int c : row) {
			cells += std::to_string(c);
		}
	}

	return "BL:" + std::to_string(type) + ";" + std::to_string(rotation) + ";" +
		std::to_string(x) + ";" + std::to_string(y) + ";" + color + ";" +
		std::to_string(n) + ";" + cells;
}

void Block::deserialize(const std::string& data) {
	if (data.compare(0, 3, "BL:") != 0) throw std::runtime_error("bad block");

	std::stringstream ss(data.substr(3));
	std::string part;

	std::getline(ss, part, ';'); int newType = std::stoi(part);
	std::getline(ss, part, ';'); int newRotation = std::stoi(part);
	std::getline(ss, part, ';'); int newX = std::stoi(part);
	std::getline(ss, part, ';'); int newY = std::stoi(part);
	std::string newColor;
	std::getline(ss, newColor, ';');

	std::getline(ss, part, ';');
	int n = std::stoi(part);
	std::string cells;
	std::getline(ss, cells, ';');

	if (newType < 0 || newType > 6 ||
		newRotation < 0 || newRotation > 3 ||
		n < 1 || n > 4 ||
		cells.size() != static_cast<size_t>(n) * n) {
		throw std::runtime_error("bad block");
	}

	std::vector<std::vector<int>> newShape(n, std::vector<int>(n));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int v = cells[i * n + j] - '0';
			if (v != 0 && v != 1) throw std::runtime_error("bad block cell");
			newShape[i][j] = v;
		}
	}

	type = newType;
	rotation = newRotation;
	x = newX;
	y = newY;
	color = newColor;
	shape = std::move(newShape);
}

std::vector<std::vector<int>> Block::calculatePlaces() const {
	std::vector<std::vector<int>> result;
	for (int i = 0; i < (int)shape.size(); i++)
	{
		for (int j = 0; j < (int)shape[i].size(); j++) {
			if (shape[i][j] == 1) {
				result.push_back({ x + j, y + i });
			}
		}
	}

	return result;
}