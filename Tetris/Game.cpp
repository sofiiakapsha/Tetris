#include "Game.h"
#include <sstream>
#include <stdexcept>

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

void Game::toMenu() { setState(std::make_unique<MenuState>()); }

void Game::setState(std::unique_ptr<State> newState) {
	nextState = std::move(newState);
}

void Game::applyState() {
	if (nextState) {
		state = std::move(nextState);
	}
}

void Game::onPauseKey() {
	applyState();
	state->onPauseKey(*this);
	applyState();
}

void Game::onStartKey() {
	applyState();
	state->onStartKey(*this);
	applyState();
}

void Game::timer(float dt) {
	if (messageTimer > 0) {
		messageTimer -= dt;
		if (messageTimer <= 0) message.clear();
	}
	applyState();
	state->update(*this, dt);
	applyState();
}

bool Game::canSave() const { return state->canSave(); }

bool Game::isGrounded() const {
	Block test = currentPiece;
	test.move(0, 1);
	return !board.canPlace(test);
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

bool Game::isCloseToLose() const {
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

const Board& Game::getBoard() const { return board; }

const Block& Game::getCurrentPiece() const { return currentPiece; }

const State& Game::getState() const { return *state; }

int Game::getScore() const { return score.getScore(); }

int Game::getBestScore() const { return score.getBest(); }

void Game::setBestScore(int s) { score.setBestScore(s); }

void Game::requestQuit() { quit = true; }

bool Game::quitRequested() const { return quit; }

std::string Game::serialize() const {
	return "GA:" + board.serialize() + "\n" +
		currentPiece.serialize() + "\n" +
		score.serialize();
}

void Game::deserialize(const std::string& data) {
	if (data.compare(0, 3, "GA:") != 0) throw std::runtime_error("bad save");

	std::stringstream ss(data.substr(3));
	std::string b, p, s;
	if (!std::getline(ss, b, '\n') ||
		!std::getline(ss, p, '\n') ||
		!std::getline(ss, s, '\n')) {
		throw std::runtime_error("bad save");
	}

	Board newBoard;
	newBoard.deserialize(b);
	Block newPiece = currentPiece;
	newPiece.deserialize(p);
	ScoreManager newScore = score;
	newScore.deserialize(s);

	if (!newBoard.canPlace(newPiece)) throw std::runtime_error("bad piece position");

	board = std::move(newBoard);
	currentPiece = std::move(newPiece);
	score = std::move(newScore);

	setState(std::make_unique<PausedState>());
	fallTimer = 0;
	lockTimer = 0;
	bonusUsed = false;
}

void Game::showMessage(const std::string& text) {
	message = text;
	messageTimer = 2.0f;
}

const std::string& Game::getMessage() const { return message; }