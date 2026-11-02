#include "Tetris.h"
#include <conio.h>
#include <windows.h>

Tetris::Tetris()
	: window(sf::VideoMode(520, 690), "Tetris", sf::Style::Titlebar | sf::Style::Close),
	input(game),
	renderer(window) {
	window.setFramerateLimit(60);
	input.bind("s", std::make_unique<SaveCommand>(saveManager));
	input.bind("l", std::make_unique<LoadCommand>(saveManager));
}


std::string Tetris::keyToString(sf::Keyboard::Key key) {
	switch (key) {
	case sf::Keyboard::Left: return "left";
	case sf::Keyboard::Right: return "right";
	case sf::Keyboard::Up: return "up";
	case sf::Keyboard::Down: return "down";
	case sf::Keyboard::Space: return " ";
	case sf::Keyboard::P: return "p";
	case sf::Keyboard::S: return "s";
	case sf::Keyboard::L: return "l";
	case sf::Keyboard::M: return "m";
	case sf::Keyboard::Q: return "q";
	default: return "";
	}
}

void Tetris::run() {
	game.setBestScore(saveManager.loadBestScore());
	int savedBest = game.getBestScore();

	sf::Clock clock;

	while (window.isOpen() && !game.quitRequested()) {
		sf::Event event;

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			else if (event.type == sf::Event::KeyPressed) {
				std::string key = keyToString(event.key.code);
				if (!key.empty()) input.onKeyPressed(key);
			}
		}

		float dt = clock.restart().asSeconds();
		if (dt > 0.1f) dt = 0.1f;
		game.timer(dt);

		window.clear(sf::Color(20, 20, 28));
		renderer.draw(game.getBoard(), game.getCurrentPiece());
		renderer.drawScore(game.getScore(), game.getBestScore());
		renderer.drawState(game.getState());
		renderer.drawMessage(game.getMessage());
		window.display();

		if (game.getBestScore() > savedBest) {
			saveManager.saveBestScore(game.getBestScore());
			savedBest = game.getBestScore();
		}
	}
}