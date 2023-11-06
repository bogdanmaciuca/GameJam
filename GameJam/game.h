#pragma once
#include "util.h"
#include <SFML/Window.hpp>
extern "C" {
#include "vendor/noise1234.h"
}

char _oldMap[MAP_W + 2][MAP_H + 2];
// Returns number of dirt/empty tiles
int UpdateMap(char map[MAP_W + 2][MAP_H + 2], bool updateWater) {
	int simple_tiles = 0;
	for (int i = 1; i < MAP_W + 1; i++) {
		for (int j = 1; j < MAP_H + 1; j++) {
			_oldMap[i][j] = map[i][j];
			if (map[i][j] == DIRT || map[i][j] == EMPTY)
				simple_tiles++;
		}
	}
	sf::Vector2i kernel[4] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
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
	return simple_tiles;
}

void CreateMap(char map[MAP_W + 2][MAP_H + 2],int &x0, int &y0) {
	srand((time(0) % 25728) * (time(0) % 81232));
	for (int i = 0; i <= MAP_W; i++)
		for (int j = 0; j <= MAP_H; j++)
			map[i][j] = -1;
	float seed_noise = ((rand() % 10000) + (rand() % 10000))/1000.0f;
	// Generate dirt
	for (int i = 1; i < MAP_W + 1; i++)
		for (int j = 1; j < MAP_H + 1; j++)
			map[i][j] = noise2((i) / seed_noise, (j) / seed_noise) > -0.18 ? DIRT : EMPTY;

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
	x = rand() % (MAP_W - 20) + 10;
	y = rand() % (MAP_H - 20) + 10;
	map[x][y] = FIRE;
}
