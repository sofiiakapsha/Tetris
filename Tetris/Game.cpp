#include "Game.h"
#include <sstream>

void Game::start() {
	board = Board();
	score.reset();
	fallTimer = 0;
	lockTimer = 0;
	bonusUsed = false;
	setState(std::make_unique<PlayingState>());
	newFigure();
}

void Game::pause() { setState(std::make_unique<PausedState>()); }

void Game::resume() { setState(std::make_unique<PlayingState>()); }

void Game::end() { setState(std::make_unique<GameOverState>()); }

void Game::toMenu() {
	setState(std::make_unique<MenuState>());
	applyState();
}

void Game::setState(std::unique_ptr<State> newState) {
	nextState = std::move(newState);
}

void Game::applyState() {
	if (nextState) {
		state = std::move(nextState);
	}
}

void Game::onPauseKey() {
	state->onPauseKey(*this);
	applyState();
}

void Game::onStartKey() {
	state->onStartKey(*this);
	applyState();
}

bool Game::canSave() { return state->canSave(); }

bool Game::isGrounded() {
	currentPiece.move(0, 1);
	bool free = board.canPlace(currentPiece);
	currentPiece.move(0, -1);
	return !free;
}

void Game::timer(float dt) {
	state->update(*this, dt);
	applyState();
}

void Game::applyGravity(float dt) {
	if (isGrounded()) {
		lockTimer += dt;
		if (lockTimer >= lockDelay) {
			lockTimer = 0;
			lockPiece();
		}
	}
	else {
		lockTimer = 0;
		fallTimer += dt;
		if (fallTimer >= fallInterval) {
			fallTimer = 0;
			currentPiece.move(0, 1);
		}
	}
}

void Game::lockPiece() {
	board.placeFigure(currentPiece);

	bool danger = isCloseToLose();
	int diff = score.getBest() - score.getScore();

	int n = board.clearLines();
	if (n > 0) {
		score.addLines(n);

		if (!bonusUsed && danger && diff > 0 && diff <= bonusRange) {
			board.addedFeature();
			int bonus = board.clearLines();
			score.addLines(bonus);
			bonusUsed = true;
		}
	}

	newFigure();
}

bool Game::isCloseToLose() {
	for (int y = 0; y < 5; y++) {
		for (int x = 0; x < board.getWidth(); x++) {
			if (board.getCell(x, y) != 0) return true;
		}
	}
	return false;
}

bool Game::moveLeft() {
	if (!state->canControl()) return false;
	currentPiece.move(-1, 0);
	if (board.canPlace(currentPiece)) { return true; }
	currentPiece.move(1, 0);
	return false;
}

bool Game::moveRight() {
	if (!state->canControl()) return false;
	currentPiece.move(1, 0);
	if (board.canPlace(currentPiece)) { return true; }
	currentPiece.move(-1, 0);
	return false;
}

bool Game::rotate() {
	if (!state->canControl()) return false;
	Block backup = currentPiece;
	currentPiece.rotate();
	if (board.canPlace(currentPiece)) return true;
	currentPiece = backup;
	return false;
}

void Game::speedUp() {
	if (!state->canControl()) return;
	currentPiece.move(0, 1);
	if (!board.canPlace(currentPiece)) currentPiece.move(0, -1);
}

void Game::hardDrop() {
	if (!state->canControl()) return;
	while (!isGrounded()) {
		currentPiece.move(0, 1);
	}
	fallTimer = 0;
	lockTimer = 0;
	lockPiece();
}

bool Game::newFigure() {
	currentPiece = factory.createRandom();
	if (!board.canPlace(currentPiece)) {
		end();
		return false;
	}
	return true;
}

Board& Game::getBoard() { return board; }

Block& Game::getCurrentPiece() { return currentPiece; }

GameState Game::getState() { return state->getType(); }

int Game::getScore() { return score.getScore(); }

int Game::getBestScore() { return score.getBest(); }

void Game::setBestScore(int s) { score.setBestScore(s); }

std::string Game::serialize() {
	return "GA:" + board.serialize() + "\n" +
		currentPiece.serialize() + "\n" +
		score.serialize();
}

void Game::deserialize(std::string data) {
	std::stringstream ss(data.substr(3));
	std::string b, p, s;
	std::getline(ss, b, '\n');
	std::getline(ss, p, '\n');
	std::getline(ss, s, '\n');

	board.deserialize(b);
	currentPiece.deserialize(p);
	score.deserialize(s);

	setState(std::make_unique<PausedState>());
	applyState();
	fallTimer = 0;
	lockTimer = 0;
}