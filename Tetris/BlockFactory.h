#pragma once
#include <random>
#include <string>
#include <vector>
#include "Block.h"

class BlockFactory {
	static const std::vector<std::vector<std::vector<int>>> shapes;
	static const std::vector<std::string> colors;
public:
	Block createRandom() const;
};