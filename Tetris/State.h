#pragma once
#include <string>

class Game;

class State {
public:
	virtual ~State() = default;
	virtual void update(Game& g, float dt) {}
	virtual void onPauseKey(Game&) {}
	virtual void onStartKey(Game&) {}
	virtual bool canControl() const { return false; }
	virtual bool canSave() const { return false; }
	virtual std::string hint() const = 0;
};

class MenuState : public State {
public:
	void onStartKey(Game& g) override;
	std::string hint() const override;
};

class PlayingState : public State {
public:
	void update(Game& g, float dt) override;
	void onPauseKey(Game& g) override;
	void onStartKey(Game& g) override;
	bool canControl() const override;
	std::string hint() const override;
};

class PausedState : public State {
public:
	void onPauseKey(Game& g) override;
	bool canSave() const override;
	std::string hint() const override;
};

class GameOverState : public State {
public:
	void onStartKey(Game& g) override;
	std::string hint() const override;
};