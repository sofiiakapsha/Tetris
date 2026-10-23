#pragma once
#include <map>
#include <string>
#include <functional>
#include "Game.h"

class InputHandler {
private:
	std::map<std::string, std::function<void()>> keyBindings;
	Game& game;
public:
	InputHandler(Game& g);
	void onKeyPressed(std::string key);
	void bind(std::string key, std::function<void()> action);
};