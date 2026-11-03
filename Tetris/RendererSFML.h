#pragma once
#include <string>
#include <SFML/Graphics.hpp>
#include "Board.h"
#include "Block.h"
#include "State.h"

class RendererSFML {
private:
	sf::RenderWindow& window;
	sf::Font font;

	void drawCell(int x, int y, const sf::Color& color);
	void drawText(const std::string& text, float x, float y, unsigned size);
public:
	RendererSFML(sf::RenderWindow& w);

	void draw(const Board& b, const Block& current);
	void drawScore(int score, int best);
	void drawState(const State& state);
	void drawMessage(const std::string& text);
};