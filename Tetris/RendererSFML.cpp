#include "RendererSFML.h"

const sf::Color colors[7] = {
	sf::Color::Cyan, sf::Color::Yellow, sf::Color(160, 60, 220),
	sf::Color::Green, sf::Color::Red, sf::Color::Blue, sf::Color(240, 150, 0)
};

RendererSFML::RendererSFML(sf::RenderWindow& w) : window(w) {
	font.loadFromFile("arial.ttf");
}

void RendererSFML::drawText(const std::string& text, float x, float y, unsigned size) {
	if (text.empty()) return;
	sf::Text t;
	t.setFont(font);
	t.setString(text);
	t.setCharacterSize(size);
	t.setFillColor(sf::Color::White);
	t.setPosition(x, y);
	window.draw(t);
}

void RendererSFML::drawCell(int x, int y, const sf::Color& color) {
	float px = 20 + x * cell + 1;
	float py = 20 + y * cell + 1;
	float size = cell - 2;

	sf::RectangleShape box(sf::Vector2f(size, size));
	box.setPosition(px, py);
	box.setFillColor(color);
	window.draw(box);

	if (color == sf::Color(40, 40, 52)) return;

	const float t = 3.f;
	sf::RectangleShape strip;

	strip.setFillColor(sf::Color(255, 255, 255, 100));
	strip.setSize(sf::Vector2f(size, t));
	strip.setPosition(px, py);
	window.draw(strip);
	strip.setSize(sf::Vector2f(t, size));
	strip.setPosition(px, py);
	window.draw(strip);

	strip.setFillColor(sf::Color(0, 0, 0, 100));
	strip.setSize(sf::Vector2f(size, t));
	strip.setPosition(px, py + size - t);
	window.draw(strip);
	strip.setSize(sf::Vector2f(t, size));
	strip.setPosition(px + size - t, py);
	window.draw(strip);
}

void RendererSFML::draw(const Board& b, const Block& current) {
	int h = b.getHeight();
	int w = b.getWidth();

	sf::RectangleShape frame(sf::Vector2f(w * cell, h * cell));
	frame.setPosition(20, 20);
	frame.setFillColor(sf::Color::Transparent);
	frame.setOutlineThickness(3.f);
	frame.setOutlineColor(sf::Color(255, 255, 255, 180));
	window.draw(frame);

	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			int c = b.getCell(x, y);
			if (c != 0) drawCell(x, y, colors[c - 1]);
			else drawCell(x, y, sf::Color(40, 40, 52));
		}
	}

	std::vector<std::vector<int>> places = current.calculatePlaces();
	for (int i = 0; i < (int)places.size(); i++) {
		int x = places[i][0];
		int y = places[i][1];
		if (x >= 0 && x < w && y >= 0 && y < h) drawCell(x, y, colors[current.getType()]);
	}
}

void RendererSFML::drawScore(int score, int best) {
	drawText("Score: " + std::to_string(score), 350, 20, 22);
	drawText("Best: " + std::to_string(best), 350, 55, 22);
}

void RendererSFML::drawState(const State& state) {
	drawText(state.hint(), 20, 632, 18);
}

void RendererSFML::drawMessage(const std::string& text) {
	drawText(text, 20, 656, 18);
}
