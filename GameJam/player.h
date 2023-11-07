#pragma once

#include "util.h"
#include <iostream>

class Player{
public:
	int GetMana() { return mana; }
	int water_tiles;
	int score;
	void Update(char map[MAP_W + 2][MAP_H + 2], sf::RenderWindow& window, int tick);
	Player(int x, int y, int mana) : x(x), y(y), mana(mana) {
		player_texture.loadFromFile("res/Contur.png");
		player_sprite.setTexture(player_texture);
		mana = MAX_MANA;
		water_tiles = 1;
		score = 0;
	};
private:
	int x, y;
	int mana, mana_refill = 1, mana_cost = 1, mana_timer = 20, mana_refill_rate = 80;
	sf::Sprite player_sprite;
	sf::Texture player_texture;
};

void Player::Update(char map[MAP_W + 2][MAP_H + 2], sf::RenderWindow& window, int tick) {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::TextEntered) {
			char c = 0;
			if (event.text.unicode < 128)
				c = static_cast<char>(event.text.unicode);
			int dir_x = 0, dir_y = 0;
			if (c == 'w')
				dir_y = -1;
			else if (c == 's')
				dir_y = +1;
			else if (c == 'a')
				dir_x = -1;
			else if (c == 'd')
				dir_x = +1;

			if (dir_y && y + dir_y > 0 && y + dir_y < MAP_H + 1) {
				if (map[x][y + dir_y] == WATER)
					y += dir_y;
				else if (mana > mana_cost) {
					y += dir_y;
					if (map[x][y + dir_y] == DIRT || map[x][y + dir_y] == FIRE)
						mana -= mana_cost;
					map[x][y] = WATER;
				}
			}
			if (dir_x && x + dir_x > 0 && x + dir_x < MAP_W + 1) {
				if (map[x + dir_x][y] == WATER)
					x += dir_x;
				else if (mana > mana_cost) {
					x += dir_x;
					if (map[x + dir_x][y] == DIRT || map[x + dir_x][y] == FIRE)
						mana -= mana_cost;
					map[x][y] = WATER;
				}
			}
		}
		else if (event.type == sf::Event::Closed)
			window.close();
	}
	mana_refill = std::max(1, water_tiles / mana_refill_rate);
	if (tick % mana_timer == 0 && mana < MAX_MANA)
		mana = std::min(mana + mana_refill, MAX_MANA);
	player_sprite.setPosition(sf::Vector2f(TILE_SIZE * (x - 1), TILE_SIZE * (y - 1)));
	window.draw(player_sprite);
	if (tick % 30 == 0)
		score++;
}


