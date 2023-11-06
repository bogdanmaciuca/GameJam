
#pragma comment(lib, "sfml-graphics")
#pragma comment(lib, "sfml-window")
#pragma comment(lib, "sfml-system")
#include "util.h"
#include "game.h"
#include "render.h"

int main() {
	char map[MAP_W+2][MAP_H+2];
	sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
	
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