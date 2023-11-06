#pragma once
#include <SFML/Graphics.hpp>
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
	sf::Color colors[5] = { sf::Color::Black, sf::Color::Green, sf::Color::Blue, {139, 69, 19} };

	for (int i = 0; i < MAP_W; i++) {
		for (int j = 0; j < MAP_H; j++) {
			if (map[i][j] != DIRT)
				tile.setFillColor(colors[map[i][j]]);
			else {
				if ((i - 1 >= 0 && map[i - 1][j] != DIRT) || (i + 1 < 0 <= MAP_W && map[i - 1][j] != DIRT) || (j - 1 >= 0 && map[i][j - 1] != DIRT) || (j + 1 < 0 <= MAP_H && map[i][j + 1] != DIRT))
					tile.setFillColor(colors[4]);
				else
					tile.setFillColor(colors[map[i][j]]);
			}
			tile.setPosition(sf::Vector2f(i * TILE_SIZE, j * TILE_SIZE));
			window.draw(tile);
		}
	}
}