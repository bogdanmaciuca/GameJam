#pragma once
#include "util.h"
#include <SFML/Window.hpp>

char _oldMap[MAP_W + 2][MAP_H + 2];
void UpdateMap(char map[MAP_W + 2][MAP_H + 2]) {
	sf::Vector2i kernel[4] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
	for (int i = 1; i < MAP_W+1; i++)
		for (int j = 1; j < MAP_H+1; j++)
			_oldMap[i][j] = map[i][j];
	for (int i = 1; i < MAP_W + 1; i++) {
		for (int j = 1; j < MAP_H + 1; j++) {
			if (_oldMap[i][j] == WATER) {
				for (int k = 0; k < 4; k++) {
					if (_oldMap[i + kernel[k].x][j + kernel[k].y] == EMPTY)
						map[i + kernel[k].x][j + kernel[k].y] = WATER;
				}
			}
		}
	}
}