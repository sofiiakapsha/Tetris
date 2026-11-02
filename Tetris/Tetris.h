#pragma once
#include <string>
#include "Game.h"
#include "RendererSFML.h"
#include "SaveManager.h"
#include "InputHandler.h"

class Tetris {
private:
	sf::RenderWindow window;
	Game game;
	RendererSFML renderer;
	SaveManager saveManager;
	InputHandler input;
	static std::string keyToString(sf::Keyboard::Key key);
public:
	Tetris();
	void run();
};