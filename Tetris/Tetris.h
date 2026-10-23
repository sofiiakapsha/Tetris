#pragma once
#include <string>
#include "Game.h"
#include "Renderer.h"
#include "SaveManager.h"
#include "InputHandler.h"

class Tetris {
private:
	Game game;
	Renderer renderer;
	SaveManager saveManager;
	InputHandler input;
	bool isRun;

	std::string readKey();
public:
	Tetris();
	void run();
};