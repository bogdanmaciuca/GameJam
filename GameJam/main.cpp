#define SFML_STATIC

#pragma comment(lib, "sfml-window")
#pragma comment(lib, "sfml-system")
#pragma comment(lib, "opengl32")
#pragma comment(lib, "winmm")
#pragma comment(lib, "gdi32")
#pragma comment(lib, "sfml-graphics")
#include <SFML/Window.hpp>

int main() {
	sf::Window window(sf::VideoMode(800, 600), "My window");
	///test
	// shit fuck asfas
	//ana are mere
	// run the program as long as the window is open
	while (window.isOpen())
	{
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