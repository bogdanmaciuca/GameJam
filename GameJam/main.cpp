#define SFML_STATIC

#pragma comment(lib, "sfml-window")
#pragma comment(lib, "sfml-system")
#pragma comment(lib, "opengl32")
#pragma comment(lib, "winmm")
#pragma comment(lib, "gdi32")
#pragma comment(lib, "sfml-graphics")
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

const int WND_WIDTH = 1024;
const int WND_HEIGHT = 768;
const int TILE_SIZE = 32;
const int MAP_W = WND_WIDTH / TILE_SIZE;
const int MAP_H = WND_HEIGHT / TILE_SIZE;

enum {
	EMPTY,
	DIRT,
	WATER,
	FIRE
};

int main() {
	char map[MAP_W][MAP_H];
	sf::Window window(sf::VideoMode(800, 600), "My window");
	
	float deltaTime;
	while (window.isOpen()) {
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
			window
			window.display();
		}
	}

	return 0;
}