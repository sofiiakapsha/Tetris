#include "InputHandler.h"

InputHandler::InputHandler(Game& g) : game(g) {
	bind("left", [&]() { game.moveLeft(); });
	bind("right", [&]() { game.moveRight(); });
	bind("up", [&]() { game.rotate(); });
	bind("down", [&]() { game.speedUp(); });
	bind("p", [&]() {
		if (game.getState() == GameState::PLAYING) game.pause();
		else if (game.getState() == GameState::PAUSED) game.resume();
		});
	bind("m", [&]() { game.toMenu(); });
}

void InputHandler::onKeyPressed(std::string key) {
	std::map<std::string, std::function<void()>>::iterator it = keyBindings.find(key);
	if (it != keyBindings.end()) {
		it->second();
	}
}

void InputHandler::bind(std::string key, std::function<void()> action) {
	keyBindings[key] = action;
}