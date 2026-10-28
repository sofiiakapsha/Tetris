#pragma once

class Game;

enum class GameState {
	MENU,
	PLAYING,
	PAUSED,
	GAME_OVER
};

class State {
public:
	virtual ~State() = default;
	virtual void update(Game& g, float dt) {}
	virtual void onPauseKey(Game& g) {}
	virtual void onStartKey(Game& g) {}
	virtual bool canControl() { return false; }
	virtual bool canSave() { return false; }
	virtual GameState getType() = 0;
};

class MenuState : public State {
public:
	void onStartKey(Game& g) override;
	GameState getType() override;
};

class PlayingState : public State {
public:
	void update(Game& g, float dt) override;
	void onPauseKey(Game& g) override;
	void onStartKey(Game& g) override;
	bool canControl() override;
	GameState getType() override;
};

class PausedState : public State {
public:
	void onPauseKey(Game& g) override;
	bool canSave() override;
	GameState getType() override;
};

class GameOverState : public State {
public:
	void onStartKey(Game& g) override;
	GameState getType() override;
};