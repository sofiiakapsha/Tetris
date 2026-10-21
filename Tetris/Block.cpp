#include "Block.h"
#include <sstream>

std::string Block::getColor() {
	return color;
}

int Block::getRotation() {
	return rotation;
}

int Block::getType() {
	return type;
}

void Block::rotate() {
	rotation = (rotation + 1) % 4;
	int n = shape.size();
	std::vector<std::vector<int>> rotated(n, std::vector<int>(n));
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			rotated[j][n - 1 - i] = shape[i][j];
	shape = rotated;
}

void Block::move(int dx, int dy) {
	x += dx;
	y += dy;
}

std::string Block::serialize() {
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
	std::stringstream ss(data.substr(3));
	std::string part;

	std::getline(ss, part, ';'); type = std::stoi(part);
	std::getline(ss, part, ';'); rotation = std::stoi(part);
	std::getline(ss, part, ';'); x = std::stoi(part);
	std::getline(ss, part, ';'); y = std::stoi(part);
	std::getline(ss, color, ';');

	std::getline(ss, part, ';');
	int n = std::stoi(part);
	std::string cells;
	std::getline(ss, cells, ';');

	shape.assign(n, std::vector<int>(n));

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			shape[i][j] = cells[i * n + j] - '0';
		}
	}
}

std::vector<std::vector<int>> Block::calculatePlaces() {
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