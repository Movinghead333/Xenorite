#pragma once

#include "qpoint.h"
#include "player_direction.h"

class World;

class Player
{
public:
	Player(int x_tile, int y_tile, int p_max_x_tiles, int p_max_y_tiles);

	PlayerDirection player_dir = PlayerDirection::UP;

	int move_ticks = 0;

	void update(PlayerDirection new_dir,
				World& world);

	QPoint tile_position;
	QPoint map_boundries;


private:
	int walking_delay;
	int walking_cooldown = 0;

	const int WALK_DELAY = 15;
	const int WALK_COOLDOWN = 15;
};