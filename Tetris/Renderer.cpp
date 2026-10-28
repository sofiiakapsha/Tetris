#include "Renderer.h"
#include <iostream>
#include <vector>
#include <windows.h>

const std::string Renderer::letters = "IOTSZJL";

Renderer::Renderer() {
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	GetConsoleCursorInfo(console, &info);
	info.bVisible = FALSE;
	SetConsoleCursorInfo(console, &info);

	hints[GameState::MENU] = "SPACE - start, L - load, Q - quit";
	hints[GameState::PLAYING] = "Arrows - move/rotate, SPACE - drop, P - pause";	hints[GameState::PAUSED] = "PAUSED: P - resume, S - save, M - menu";
	hints[GameState::GAME_OVER] = "GAME OVER: SPACE - again, M - menu";
}

void Renderer::draw(const Board& b, Block current) {
	int w = b.getWidth();
	int h = b.getHeight();
	std::vector<std::string> lines(h, std::string(w, '.'));

	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			int cell = b.getCell(x, y);
			if (cell != 0) lines[y][x] = letters[cell - 1];
		}
	}

	std::vector<std::vector<int>> places = current.calculatePlaces();
	for (int i = 0; i < (int)places.size(); i++) {
		int x = places[i][0];
		int y = places[i][1];
		if (x >= 0 && x < w && y >= 0 && y < h) lines[y][x] = '#';
	}

	std::string frame;
	for (int y = 0; y < h; y++) {
		frame += "|" + lines[y] + "|\n";
	}
	frame += "+" + std::string(w, '-') + "+\n";

	COORD pos = { 0, 0 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	std::cout << frame;
}

void Renderer::drawScore(int score, int best) {
	std::string text = "Score: " + std::to_string(score) + "   Best: " + std::to_string(best);
	text.resize(45, ' ');
	std::cout << text << "\n";
}

void Renderer::drawState(GameState state) {
	std::string text = hints[state];
	text.resize(45, ' ');
	std::cout << text << "\n";
}