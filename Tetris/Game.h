#pragma once
#include "Board.h"
#include "BlockFactory.h"
#include "ScoreManager.h"
#include "Block.h"
#include "State.h"
#include <memory>

class Game {
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

	bool isGrounded();
	bool isCloseToLose();
	void lockPiece();
	void applyState();

public:
	Game() : currentPiece(factory.createRandom()), state(std::make_unique<MenuState>()), score(0, 0), fallTimer(0), lockTimer(0),
		fallInterval(0.5f), lockDelay(0.3f), bonusUsed(false), bonusRange(50) {
	};

	void start();
	void pause();
	void resume();
	void end();
	void toMenu();
	void timer(float dt);
	void applyGravity(float dt);
	void setState(std::unique_ptr<State> newState);
	void onPauseKey();
	void onStartKey();
	bool canSave();
	bool moveLeft();
	bool moveRight();
	bool rotate();
	bool newFigure();
	void speedUp();
	void hardDrop();

	Board& getBoard();
	Block& getCurrentPiece();
	GameState getState();
	int getScore();
	int getBestScore();
	void setBestScore(int s);

	std::string serialize();
	void deserialize(std::string data);
};