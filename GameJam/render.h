#pragma once
#include "util.h"

void DrawMap(char map[MAP_W + 2][MAP_H + 2], sf::RenderWindow& window) {
	sf::RectangleShape tile({ TILE_SIZE, TILE_SIZE });
	sf::Texture textures[5];
	textures[0].loadFromFile("res/stone.png");
	textures[1].loadFromFile("res/grass.png");
	textures[2].loadFromFile("res/water.png");
	textures[3].loadFromFile("res/lava.png");
	textures[4].loadFromFile("res/dirt.png");

	for (int i = 1; i <= MAP_W; i++) {
		for (int j = 1; j <= MAP_H; j++) {
			if (map[i][j] != DIRT)
				tile.setTexture(&textures[map[i][j]]);
			else if ((map[i - 1][j] != DIRT || map[i + 1][j] != DIRT || map[i][j - 1] != DIRT || map[i][j + 1] != DIRT)
				&& (map[i - 1][j] != FIRE || map[i + 1][j] != FIRE || map[i][j - 1] != FIRE || map[i][j + 1] != FIRE))
				tile.setTexture(&textures[4]);
			else
				tile.setTexture(&textures[map[i][j]]);
			tile.setPosition(sf::Vector2f((i - 1) * TILE_SIZE, (j - 1) * TILE_SIZE));
			window.draw(tile);
		}
	}
}

void DrawGUI(sf::RenderWindow& window, int mana, int simpleTiles) {
	int width = 200, height = 40;
	{
		sf::RectangleShape outter({ (float)width + 20, (float)height + 20 });
		sf::RectangleShape inner({ (float)width, (float)height });
		sf::RectangleShape active({ (float)width * mana / MAX_MANA, (float)height });

		outter.setFillColor({ 145, 145, 145, 200 });
		inner.setFillColor({ 0, 23, 153, 180 });
		active.setFillColor({ 0, 15, 140, 180 });
		outter.setPosition({ 20, 20 });
		inner.setPosition({ 30, 30 });
		active.setPosition({ 30, 30 });
		window.draw(outter);
		window.draw(inner);
		window.draw(active);
	}
	{
		sf::RectangleShape outter({ (float)width + 20, (float)height + 20 });
		sf::RectangleShape inner({ (float)width, (float)height });
		sf::RectangleShape active({ (float)width * (simpleTiles - 200) / (MAP_W*MAP_H - 200), (float)height});
		
		outter.setFillColor({ 145, 145, 145, 200 });
		inner.setFillColor({ 170, 0, 0, 120});
		active.setFillColor({ 200, 0, 0, 160});
		outter.setPosition({ (float)width + 60, 20.0f });
		inner.setPosition({ (float)width + 70, 30.0f });
		active.setPosition({ (float)width + 70, 30.0f });
		window.draw(outter);
		window.draw(inner);
		window.draw(active);
	}
}
