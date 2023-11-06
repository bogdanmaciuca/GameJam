#pragma once
#include "util.h"

void DrawMap(char map[MAP_W + 2][MAP_H + 2], sf::RenderWindow& window) {

	/*
	sf::Texture dirt_tex[4], water_tex, fire_tex;
	dirt_tex[0].loadFromFile("res/");
	dirt_tex[1].loadFromFile("res/");
	dirt_tex[2].loadFromFile("res/");
	dirt_tex[4].loadFromFile("res/");
	water_tex.loadFromFile("res/");
	fire_tex.loadFromFile("res/");
	*/

	sf::RectangleShape tile({ TILE_SIZE, TILE_SIZE });
	sf::Color colors[5] = { sf::Color::Black, sf::Color::Green, sf::Color::Blue, sf::Color::Red ,{139, 69, 19} };

	for (int i = 1; i <= MAP_W; i++) {
		for (int j = 1; j <= MAP_H; j++) {
			if (map[i][j] != DIRT)
				tile.setFillColor(colors[map[i][j]]);
			else if (map[i - 1][j] != DIRT || map[i + 1][j] != DIRT || map[i][j - 1] != DIRT || map[i][j + 1] != DIRT)
				tile.setFillColor(colors[4]);
			else
				tile.setFillColor(colors[map[i][j]]);
			tile.setPosition(sf::Vector2f((i - 1) * TILE_SIZE, (j - 1) * TILE_SIZE));
			window.draw(tile);
		}
	}
}