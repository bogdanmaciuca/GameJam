
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

int main() {
	char map[MAP_W + 2][MAP_H + 2];
	int start_x, start_y; //pozitia initiala a caracterului
	CreateMap(map, start_x, start_y);

	sf::RenderWindow window(sf::VideoMode(WND_WIDTH, WND_HEIGHT), "Minesweeper");
	Player player(start_x, start_y, MAX_MANA);

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
		DrawGUI(window, player.GetMana());
		window.display();
		ticks++;
	}

	return 0;
}