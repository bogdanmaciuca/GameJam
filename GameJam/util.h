#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

const int WND_WIDTH = 1024;
const int WND_HEIGHT = 768;
const int TILE_SIZE = 16;
const int MAP_W = WND_WIDTH / TILE_SIZE;
const int MAP_H = WND_HEIGHT / TILE_SIZE;
const int MAX_MANA = 10;
enum {
	EMPTY,
	DIRT,
	WATER,
	FIRE
};

const int FPS_LIMIT = 30;
const int MAX_MANA = 10;
