
#pragma comment(lib, "sfml-graphics")
#pragma comment(lib, "sfml-window")
#pragma comment(lib, "sfml-system")
#include "util.h"
#include "game.h"
#include "render.h"
extern "C" {
#include "vendor/noise1234.h"
}
#include <iostream>

int main() {
	char map[MAP_W+2][MAP_H+2];
	for (int i = 0; i <= MAP_W; i++)
		for (int j = 0; j <= MAP_H; j++)
			map[i][j] = -1;

	for (int i = 1; i < MAP_W; i++)
		for (int j = 1; j < MAP_H; j++)
			map[i][j] = (noise2(i/10.0f, j / 10.0f) > -.25f ? DIRT : EMPTY);
	
	sf::RenderWindow window(sf::VideoMode(WND_WIDTH, WND_HEIGHT), "My window");
	
	window.setFramerateLimit(FPS_LIMIT);
	unsigned long long ticks = 0;
	while (window.isOpen()) {
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// Game logic
		if (ticks % 30 == 0)
			UpdateMap(map);

		// Render
		window.clear();
		DrawMap(map, window);
		window.display();
		ticks++;
	}
	
		

	return 0;
}