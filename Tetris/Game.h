#pragma once
#include "Board.h"
#include "BlockFactory.h"
#include "ScoreManager.h"
#include "Block.h"

enum class GameState {
	MENU,
	PLAYING,
	PAUSED,
	GAME_OVER
};

class Game {
private:
	BlockFactory factory;
	Board board;
	Block currentPiece;
	GameState state;
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

public:
	Game() : currentPiece(factory.createRandom()), state(GameState::MENU), score(0, 0), fallTimer(0), lockTimer(0),
		fallInterval(0.5f), lockDelay(0.3f), bonusUsed(false), bonusRange(50) {
	};

	void start();
	void pause();
	void resume();
	void end();
	void toMenu();
	void timer(float dt);
	bool moveLeft();
	bool moveRight();
	bool rotate();
	void speedUp();
	bool newFigure();

	Board& getBoard();
	Block& getCurrentPiece();
	GameState getState();
	int getScore();
	int getBestScore();
	void setBestScore(int s);

	std::string serialize();
	void deserialize(std::string data);
};