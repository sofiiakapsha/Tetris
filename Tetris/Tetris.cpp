#include "Tetris.h"
#include <conio.h>
#include <windows.h>

Tetris::Tetris() : input(game), isRun(true) {
	input.bind("s", [&]() {
		if (game.getState() == GameState::PAUSED) {
			saveManager.save("save.txt", game.serialize());
		}
		});

	input.bind("l", [&]() {
		std::string data = saveManager.load("save.txt");
		if (!data.empty()) {
			int best = game.getBestScore();
			game.deserialize(data);
			if (game.getBestScore() < best) game.setBestScore(best);
		}
		});
	input.bind(" ", [&]() {
		if (game.getState() == GameState::MENU || game.getState() == GameState::GAME_OVER) {
			game.start();
		}
		});
	input.bind("q", [&]() { isRun = false; });
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
	bool bestSaved = false;

	while (isRun) {
		if (_kbhit()) {
			input.onKeyPressed(readKey());
		}

		game.timer(0.05f);

		renderer.draw(game.getBoard(), game.getCurrentPiece());
		renderer.drawScore(game.getScore(), game.getBestScore());
		renderer.drawState(game.getState());

		if (game.getState() == GameState::GAME_OVER && !bestSaved) {
			saveManager.saveBestScore(game.getBestScore());
			bestSaved = true;
		}
		if (game.getState() == GameState::PLAYING) {
			bestSaved = false;
		}

		Sleep(50);
	}

	saveManager.saveBestScore(game.getBestScore());
}