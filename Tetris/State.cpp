#include "State.h"
#include "Game.h"

void MenuState::onStartKey(Game& g) { g.start(); }

std::string MenuState::hint() const { return "SPACE - start, L - load, Q - quit"; }


void PlayingState::update(Game& g, float dt) { g.applyGravity(dt); }

void PlayingState::onPauseKey(Game& g) { g.pause(); }

void PlayingState::onStartKey(Game& g) { g.hardDrop(); }

bool PlayingState::canControl() const { return true; }

std::string PlayingState::hint() const { return "Arrows - move/rotate, SPACE - drop, P - pause"; }


void PausedState::onPauseKey(Game& g) { g.resume(); }

bool PausedState::canSave() const { return true; }

std::string PausedState::hint() const { return "PAUSED: P - resume, S - save, M - menu"; }


void GameOverState::onStartKey(Game& g) { g.start(); }

std::string GameOverState::hint() const { return "GAME OVER: SPACE - again, M - menu"; }