#include "Command.h"
#include <string>

void MoveLeftCommand::execute(Game& g) { g.moveLeft(); }

void MoveRightCommand::execute(Game& g) { g.moveRight(); }

void RotateCommand::execute(Game& g) { g.rotate(); }

void SpeedUpCommand::execute(Game& g) { g.speedUp(); }

void PauseCommand::execute(Game& g) { g.onPauseKey(); }

void StartCommand::execute(Game& g) { g.onStartKey(); }

void MenuCommand::execute(Game& g) { g.toMenu(); }

void SaveCommand::execute(Game& g) {
	if (g.canSave()) {
		saveManager.save("save.txt", g.serialize());
	}
}

void LoadCommand::execute(Game& g) {
	std::string data = saveManager.load("save.txt");
	if (!data.empty()) {
		int best = g.getBestScore();
		g.deserialize(data);
		if (g.getBestScore() < best) g.setBestScore(best);
	}
}

void QuitCommand::execute(Game& g) { isRun = false; }