#pragma once
#include <map>
#include <string>
#include <memory>
#include "Game.h"
#include "Command.h"

class InputHandler {
private:
	std::map<std::string, std::unique_ptr<Command>> keyBindings;
	Game& game;
public:
	InputHandler(Game& g);
	void onKeyPressed(std::string key);
	void bind(std::string key, std::unique_ptr<Command> command);
};