#pragma once
#include "util.h"
#include <iostream>
#include <SFML/Window.hpp>
#include <random>
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

bool isPrime(int n)
{
	if (n <= 1)
		return false;

	for (int i = 2; i <= n / 2; i++)
		if (n % i == 0)
			return false;

	return true;
}

void CreateMap(char map[MAP_W + 2][MAP_H + 2],int &x0, int &y0) {
	for (int i = 0; i <= MAP_W; i++)
		for (int j = 0; j <= MAP_H; j++)
			map[i][j] = -1;

	srand(time(NULL));
	int rand_seed = 150+rand()%30;
	std::cout << rand_seed;
	// Generate dirt
	for (int i = 1; i < MAP_W + 1; i++)
		for (int j = 1; j < MAP_H + 1; j++) 
			map[i][j] = noise2((float)(i * 10) / (rand_seed %100), (float)(j * 10) / (rand_seed % 100)) > -0.185 ? DIRT : EMPTY;

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