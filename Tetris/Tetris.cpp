#include "Tetris.h"
#include <conio.h>
#include <windows.h>

Tetris::Tetris() : input(game), isRun(true) {
	input.bind("s", std::make_unique<SaveCommand>(saveManager));
	input.bind("l", std::make_unique<LoadCommand>(saveManager));
	input.bind("q", std::make_unique<QuitCommand>(isRun));
}

std::string Tetris::readKey() {
	int c = _getch();
	if (c == 0 || c == 224) {
		int code = _getch();
		if (code == 72) return "up";
		if (code == 80) return "down";
		if (code == 75) return "left";
		if (code == 77) return "right";
		return "";
	}
	return std::string(1, (char)c);
}

void Tetris::run() {
	game.setBestScore(saveManager.loadBestScore());
	int savedBest = game.getBestScore();

	while (isRun) {
		if (_kbhit()) {
			input.onKeyPressed(readKey());
		}

		game.timer(0.05f);

		renderer.draw(game.getBoard(), game.getCurrentPiece());
		renderer.drawScore(game.getScore(), game.getBestScore());
		renderer.drawState(game.getState());

		if (game.getBestScore() > savedBest) {
			saveManager.saveBestScore(game.getBestScore());
			savedBest = game.getBestScore();
		}

		Sleep(50);
	}
}