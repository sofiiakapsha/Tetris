#include "Game.h"
#include <sstream>

void Game::start() {
	board = Board();
	score.reset();
	fallTimer = 0;
	lockTimer = 0;
	bonusUsed = false;
	state = GameState::PLAYING;
	newFigure();
}

void Game::pause() { state = GameState::PAUSED; }

void Game::resume() { state = GameState::PLAYING; }

void Game::end() { state = GameState::GAME_OVER; }

void Game::toMenu() { state = GameState::MENU; }

bool Game::isGrounded() {
	currentPiece.move(0, 1);
	bool free = board.canPlace(currentPiece);
	currentPiece.move(0, -1);
	return !free;
}

void Game::timer(float dt) {
	if (state != GameState::PLAYING) return;

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
	if (state != GameState::PLAYING) return false;
	currentPiece.move(-1, 0);
	if (board.canPlace(currentPiece)) { return true; }
	currentPiece.move(1, 0);
	return false;
}

bool Game::moveRight() {
	if (state != GameState::PLAYING) return false;
	currentPiece.move(1, 0);
	if (board.canPlace(currentPiece)) { return true; }
	currentPiece.move(-1, 0);
	return false;
}

bool Game::rotate() {
	if (state != GameState::PLAYING) return false;
	Block backup = currentPiece;
	currentPiece.rotate();
	if (board.canPlace(currentPiece)) return true;
	currentPiece = backup;
	return false;
}

void Game::speedUp() {
	if (state != GameState::PLAYING) return;
	currentPiece.move(0, 1);
	if (!board.canPlace(currentPiece)) currentPiece.move(0, -1);
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

GameState Game::getState() { return state; }

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

	state = GameState::PAUSED;
	fallTimer = 0;
	lockTimer = 0;
}