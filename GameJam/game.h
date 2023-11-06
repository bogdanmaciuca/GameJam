#pragma once
#include "util.h"
#include <SFML/Window.hpp>
extern "C" {
#include "vendor/noise1234.h"
}

char _oldMap[MAP_W + 2][MAP_H + 2];
void UpdateMap(char map[MAP_W + 2][MAP_H + 2], bool updateWater) {
	sf::Vector2i kernel[4] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
	for (int i = 1; i < MAP_W+1; i++)
		for (int j = 1; j < MAP_H+1; j++)
			_oldMap[i][j] = map[i][j];
	for (int i = 1; i < MAP_W + 1; i++) {
		for (int j = 1; j < MAP_H + 1; j++) {
			if (_oldMap[i][j] == (updateWater ? WATER : FIRE)) {
				for (int k = 0; k < 4; k++) {
					if (updateWater) {
						if (_oldMap[i + kernel[k].x][j + kernel[k].y] == EMPTY)
							map[i + kernel[k].x][j + kernel[k].y] = WATER;
					}
					else {
						bool update = (rand() % 10) > 3;
						if (update && (_oldMap[i + kernel[k].x][j + kernel[k].y] == EMPTY || _oldMap[i + kernel[k].x][j + kernel[k].y] == DIRT))
							map[i + kernel[k].x][j + kernel[k].y] = FIRE;
					}
				}
			}
		}
	}
}

void CreateMap(char map[MAP_W + 2][MAP_H + 2],int &x0, int &y0) {
	srand(time(0));
	for (int i = 0; i <= MAP_W; i++)
		for (int j = 0; j <= MAP_H; j++)
			map[i][j] = -1;

	// Generate dirt
	for (int i = 1; i < MAP_W + 1; i++)
		for (int j = 1; j < MAP_H + 1; j++) {
			int offset = rand() % 1000;
			map[i][j] = noise2((8639 + i) / 10.0f, (8639 + j) / 10.0f) > -.25f ? DIRT : EMPTY;
		}

	// Generate water
	int x = 0, y = 0;
	do {
		x = rand() % MAP_W + 1;
		y = rand() % MAP_H + 1;
	} while (map[x][y] != EMPTY);
	map[x][y] = WATER;
	x0 = x;
	y0 = y;

	// Generate fire
	x = rand() % (MAP_W - 10) + 5;
	y = rand() % (MAP_W - 10) + 5;
	map[x][y] = FIRE;
}
