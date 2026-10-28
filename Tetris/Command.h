#pragma once
#include "Game.h"
#include "SaveManager.h"

class Command {
public:
	virtual ~Command() = default;
	virtual void execute(Game& g) = 0;
};

class MoveLeftCommand : public Command {
public:
	void execute(Game& g) override;
};

class MoveRightCommand : public Command {
public:
	void execute(Game& g) override;
};

class RotateCommand : public Command {
public:
	void execute(Game& g) override;
};

class SpeedUpCommand : public Command {
public:
	void execute(Game& g) override;
};

class PauseCommand : public Command {
public:
	void execute(Game& g) override;
};

class StartCommand : public Command {
public:
	void execute(Game& g) override;
};

class MenuCommand : public Command {
public:
	void execute(Game& g) override;
};

class SaveCommand : public Command {
private:
	SaveManager& saveManager;
public:
	SaveCommand(SaveManager& sm) : saveManager(sm) {}
	void execute(Game& g) override;
};

class LoadCommand : public Command {
private:
	SaveManager& saveManager;
public:
	LoadCommand(SaveManager& sm) : saveManager(sm) {}
	void execute(Game& g) override;
};

class QuitCommand : public Command {
private:
	bool& isRun;
public:
	QuitCommand(bool& run) : isRun(run) {}
	void execute(Game& g) override;
};