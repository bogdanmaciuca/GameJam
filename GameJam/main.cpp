
#pragma comment(lib, "sfml-graphics")
#pragma comment(lib, "sfml-window")
#pragma comment(lib, "sfml-system")
#include "util.h"
#include "game.h"
#include "render.h"
#include <stdlib.h>
#include <iostream>
#include <iostream>
#include "player.h"

void DrawGUI(sf::RenderWindow &window) {
	sf::RectangleShape outter({ 220, 60 }), inner({200, 40});
	outter.setFillColor({ 145, 145, 145, 200});
	inner.setFillColor({ 0, 23, 153, 200 });
	outter.setPosition({ 20, 20 });
	inner.setPosition({ 30, 30 });
	window.draw(outter);
	window.draw(inner);
}

int main() {
	char map[MAP_W + 2][MAP_H + 2];
	int start_x, start_y; //pozitia initiala a caracterului
	CreateMap(map, start_x, start_y);

	sf::RenderWindow window(sf::VideoMode(WND_WIDTH, WND_HEIGHT), "Minesweeper");
	Player player(start_x, start_y);

	window.setFramerateLimit(FPS_LIMIT);
	unsigned long long ticks = 0;
	while (window.isOpen()) {
		// Game logic
		if (ticks % 15 == 0)
			UpdateMap(map, 1); // Updates water
		if (ticks % 60 == 0)
			UpdateMap(map, 0); // Updates fire

		// Render
		window.clear();

		DrawMap(map, window);
		player.Update(map, window, ticks);
		DrawGUI(window);
		window.display();
		ticks++;
	}

	return 0;
}