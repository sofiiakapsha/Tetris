#include "State.h"
#include "Game.h"

void MenuState::onStartKey(Game& g) { g.start(); }

GameState MenuState::getType() { return GameState::MENU; }


void PlayingState::update(Game& g, float dt) { g.applyGravity(dt); }

void PlayingState::onPauseKey(Game& g) { g.pause(); }

bool PlayingState::canControl() { return true; }

GameState PlayingState::getType() { return GameState::PLAYING; }

void PlayingState::onStartKey(Game& g) { g.hardDrop(); }


void PausedState::onPauseKey(Game& g) { g.resume(); }

bool PausedState::canSave() { return true; }

GameState PausedState::getType() { return GameState::PAUSED; }


void GameOverState::onStartKey(Game& g) { g.start(); }

GameState GameOverState::getType() { return GameState::GAME_OVER; }