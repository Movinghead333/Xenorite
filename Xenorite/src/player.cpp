#include "player.h"
#include <iostream>

Player::Player(int x_tile, int y_tile, int p_max_x_tiles, int p_max_y_tiles)
	:
	tile_position(QPoint(x_tile, y_tile)),
	map_boundries(QPoint(p_max_x_tiles, p_max_y_tiles))
{
}

void Player::update(PlayerDirection new_dir)
{
	if (new_dir == player_dir)
	{
		if (walking_delay < WALK_DELAY)
		{
			walking_delay++;
		}
		else
		{
			if (walking_cooldown == 0)
			{
				// walk
				switch (player_dir)
				{
				case UP:
					if (tile_position.y() != 0)
						tile_position.setY(tile_position.y() - 1);
					break;
				case RIGHT:
					if ((tile_position.x() + 1) != map_boundries.x())
						tile_position.setX(tile_position.x() + 1);
					break;
				case DOWN:
					if ((tile_position.y() + 1) != map_boundries.y())
						tile_position.setY(tile_position.y() + 1);
					break;
				case LEFT:
					if (tile_position.x() != 0)
						tile_position.setX(tile_position.x() - 1);
					break;
				default:
					break;
				}

				// set cd
				walking_cooldown = WALK_COOLDOWN;
			}
			else if (walking_cooldown > 0)
			{
				walking_cooldown--;
			}
		}
	}
	else
	{
		player_dir = new_dir;
		walking_delay = 0;
	}
}
