#include "Command.h"
#include <string>
#include <exception>

void MoveLeftCommand::execute(Game& g) { g.moveLeft(); }

void MoveRightCommand::execute(Game& g) { g.moveRight(); }

void RotateCommand::execute(Game& g) { g.rotate(); }

void SpeedUpCommand::execute(Game& g) { g.speedUp(); }

void PauseCommand::execute(Game& g) { g.onPauseKey(); }

void StartCommand::execute(Game& g) { g.onStartKey(); }

void MenuCommand::execute(Game& g) { g.toMenu(); }

void SaveCommand::execute(Game& g) {
	if (g.canSave()) {
		if (saveManager.save("save.txt", g.serialize())) g.showMessage("Game saved");
		else g.showMessage("Could not save");
	}
}

void LoadCommand::execute(Game& g) {
	std::string data = saveManager.load("save.txt");
	if (data.empty()) {
		g.showMessage("No save file");
		return;
	}

	int best = g.getBestScore();
	try {
		g.deserialize(data);
	}
	catch (const std::exception&) {
		g.showMessage("Save file is corrupted");
		return;
	}
	if (g.getBestScore() < best) g.setBestScore(best);
	g.showMessage("Game loaded");
}

void QuitCommand::execute(Game& g) { g.requestQuit(); }