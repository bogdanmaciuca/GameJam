#pragma once
#include "util.h"
#include <SFML/Window.hpp>
extern "C" {
#include "vendor/noise1234.h"
}

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

void CreateMap(char map[MAP_W + 2][MAP_H + 2],int &x0, int &y0) {
	for (int i = 0; i <= MAP_W; i++)
		for (int j = 0; j <= MAP_H; j++)
			map[i][j] = -1;

	for (int i = 1; i < MAP_W + 1; i++)
		for (int j = 1; j < MAP_H + 1; j++)
			map[i][j] = (noise2(i / 10.0f, j / 10.0f) > -.25f ? DIRT : EMPTY);

	// Generate water
	int waterStartX = 0, waterStartY = 0;
	srand(time(0));
	do {
		waterStartX = rand() % MAP_W + 1;
		waterStartY = rand() % MAP_H + 1;
	} while (map[waterStartX][waterStartY] != EMPTY);
	map[waterStartX][waterStartY] = WATER;
	x0 = waterStartX;
	y0 = waterStartY;
}