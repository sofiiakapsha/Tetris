#pragma once
#include "Board.h"
#include "BlockFactory.h"
#include "ScoreManager.h"
#include "Block.h"
#include "State.h"
#include <memory>
#include <string>

class Game {
	friend class MenuState;
	friend class PlayingState;
	friend class PausedState;
	friend class GameOverState;

private:
	BlockFactory factory;
	Board board;
	Block currentPiece;
	std::unique_ptr<State> state;
	std::unique_ptr<State> nextState;
	ScoreManager score;
	float fallTimer;
	float lockTimer;
	float fallInterval;
	float lockDelay;
	bool bonusUsed;
	int bonusRange;
	bool quit;

	std::string message;
	float messageTimer;

	void start();
	void pause();
	void resume();
	void end();
	void hardDrop();
	void applyGravity(float dt);

	void setState(std::unique_ptr<State> newState);
	void applyState();

	void lockPiece();
	bool newFigure();
	bool isGrounded() const;
	bool isCloseToLose() const;

public:
	Game() : currentPiece(factory.createRandom()), state(std::make_unique<MenuState>()), score(0, 0), fallTimer(0), lockTimer(0),
		fallInterval(0.5f), lockDelay(0.3f), bonusUsed(false), bonusRange(100), quit(false), message(""), messageTimer(0) {
	}

	void timer(float dt);
	void onPauseKey();
	void onStartKey();
	void toMenu();

	bool moveLeft();
	bool moveRight();
	bool rotate();
	void speedUp();

	bool canSave() const;

	const Board& getBoard() const;
	const Block& getCurrentPiece() const;
	const State& getState() const;
	int getScore() const;
	int getBestScore() const;
	void setBestScore(int s);

	void requestQuit();
	bool quitRequested() const;

	std::string serialize() const;
	void deserialize(const std::string& data);

	void showMessage(const std::string& text);
	const std::string& getMessage() const;
};