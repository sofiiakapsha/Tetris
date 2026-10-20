#include "BlockFactory.h"

const std::vector<std::vector<std::vector<int>>> BlockFactory::shapes = {
	{ {0,0,0,0},
	  {1,1,1,1},
	  {0,0,0,0},
	  {0,0,0,0} },

	{ {1,1},
	  {1,1} },

	{ {0,1,0},
	  {1,1,1},
	  {0,0,0} },

	{ {0,1,1},
	  {1,1,0},
	  {0,0,0} },

	{ {1,1,0},
	  {0,1,1},
	  {0,0,0} },

	{ {1,0,0},
	  {1,1,1},
	  {0,0,0} },

	{ {0,0,1},
	  {1,1,1},
	  {0,0,0} }
};

const std::vector<std::string> BlockFactory::colors = {
	"cyan", "yellow", "purple", "green", "red", "blue", "orange"
};

Block BlockFactory::createRandom() const {
	static std::mt19937 gen(std::random_device{}());
	std::uniform_int_distribution<int> distrib(0, 6);
	int type = distrib(gen);

	return Block(type, 3, 5, 0, colors[type], shapes[type]);
}