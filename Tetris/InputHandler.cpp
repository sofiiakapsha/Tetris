#include "InputHandler.h"

InputHandler::InputHandler(Game& g) : game(g) {
	bind("left", std::make_unique<MoveLeftCommand>());
	bind("right", std::make_unique<MoveRightCommand>());
	bind("up", std::make_unique<RotateCommand>());
	bind("down", std::make_unique<SpeedUpCommand>());
	bind("p", std::make_unique<PauseCommand>());
	bind(" ", std::make_unique<StartCommand>());
	bind("m", std::make_unique<MenuCommand>());
}

void InputHandler::onKeyPressed(std::string key) {
	std::map<std::string, std::unique_ptr<Command>>::iterator it = keyBindings.find(key);
	if (it != keyBindings.end()) {
		it->second->execute(game);
	}
}

void InputHandler::bind(std::string key, std::unique_ptr<Command> command) {
	keyBindings[key] = std::move(command);
}