
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
	int start_x, start_y; // pozitia initiala a caracterului
	int timeBetweenFires = 5; // In seconds
	bool gameOver = false;
	CreateMap(map, start_x, start_y);

	sf::RenderWindow window(sf::VideoMode(WND_WIDTH, WND_HEIGHT), "Minesweeper");
	Player player(start_x, start_y, MAX_MANA);
	sf::Texture gameOverTex;
	gameOverTex.loadFromFile("res/game_over.png");
	sf::Sprite gameOverSprite;
	gameOverSprite.setPosition(0, 0);
	gameOverSprite.setScale(1.0f / gameOverTex.getSize().x * WND_WIDTH, 1.0f / gameOverTex.getSize().y * WND_HEIGHT);
	gameOverSprite.setTexture(gameOverTex);
	sf::Texture splashScreenTex;
	splashScreenTex.loadFromFile("res/splashscreen.png");
	sf::Sprite splashScreenSprite;
	splashScreenSprite.setPosition(0, 0);
	splashScreenSprite.setScale(1.0f / splashScreenTex.getSize().x * WND_WIDTH, 1.0f / splashScreenTex.getSize().y * WND_HEIGHT);
	splashScreenSprite.setTexture(splashScreenTex);

	window.draw(splashScreenSprite);
	window.display();
	while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		player.Update(map, window, 0);
	
	window.setFramerateLimit(FPS_LIMIT);
	unsigned long long ticks = 0;
	while (window.isOpen()) {
		int simpleTiles;
		// Game logic
		if (ticks % 15 == 0)
			simpleTiles = UpdateMap(map, 1, player.water_tiles); // Updates water
		if (ticks % 60 == 0)
			UpdateMap(map, 0, player.water_tiles); // Updates fire
		if (ticks != 0 && ticks % (FPS_LIMIT * timeBetweenFires) == 0) { // Spawn new fire
			int x, y;
			do {
				x = rand() % (MAP_W - 20) + 10;
				y = rand() % (MAP_H - 20) + 10;
			} while (map[x][y] == FIRE || map[x][y] == WATER);
			map[x][y] = FIRE;
		}
		gameOver = false;
		if (simpleTiles < 200) {
			gameOver = true;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) { // Reset
				CreateMap(map, start_x, start_y);
				player = Player(start_x, start_y, MAX_MANA);
			}
		}

		// Render
		window.clear();
		DrawMap(map, window);
		player.Update(map, window, ticks);
		DrawGUI(window, player.GetMana(), simpleTiles);
		if (gameOver) window.draw(gameOverSprite);
		window.display();
		ticks++;
	}

	return 0;
}