#pragma once
#include <string>
#include <vector>

class Block {
private:
	int type;
	int rotation;
	int x, y;
	std::string color;
	std::vector<std::vector<int>> shape;

public:
	Block(int type, int rotation, int x, int y, std::string color) :
		type(type), rotation(rotation), x(x), y(y), color(color) {}

	std::string getColor();
	int getRotation();
	int getType();
	void rotate();
	void move(int dx, int dy);
	std::string serialize();
	void deserialize(const std::string& data);
	std::vector<std::vector<int>> calculatePlaces();
};