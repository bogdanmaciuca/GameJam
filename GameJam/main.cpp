#define SFML_STATIC

#pragma comment(lib, "sfml-window")
#pragma comment(lib, "sfml-system")
#pragma comment(lib, "opengl32")
#pragma comment(lib, "winmm")
#pragma comment(lib, "gdi32")
#pragma comment(lib, "sfml-graphics")
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

int main() {
	char map[TILE_NUM_X][TILE_NUM_Y];
	sf::Window window(sf::VideoMode(800, 600), "My window");
	while (window.isOpen()) {
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
			window.display();
		}
	}

	return 0;
}