#include "player.h"

#include <iostream>

#include "world.h"

Player::Player(int x_tile, int y_tile, int p_max_x_tiles, int p_max_y_tiles)
	:
	tile_position(QPoint(x_tile, y_tile)),
	map_boundries(QPoint(p_max_x_tiles, p_max_y_tiles))
{
	inventory.add_item(ItemStack(ItemType::ROCK, 5));
	inventory.add_item(ItemStack(ItemType::KRONOMITE_ORE, 10));
	inventory.add_item(ItemStack(ItemType::XENORITE_ORE, 20));

	std::cout << inventory.to_string() << std::endl;
}

void Player::update(PlayerDirection new_dir,
					World& world)
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
				int target_x = tile_position.x();
				int target_y = tile_position.y();
				// walk
				switch (player_dir)
				{
				case UP:
					target_y--;
					if (target_y >= 0)
					{
						if (!world.get_tile(target_x, target_y).collision)
						{
							tile_position.setY(target_y);
						}
					}
					break;
				case RIGHT:
					target_x++;
					if (target_x < map_boundries.x())
					{
						if (!world.get_tile(target_x, target_y).collision)
						{
							tile_position.setX(target_x);
						}
					}
					break;
				case DOWN:
					target_y++;
					if (target_y < map_boundries.y())
					{
						if (!world.get_tile(target_x, target_y).collision)
						{
							tile_position.setY(target_y);
						}
					}
					break;
				case LEFT:
					target_x--;
					if (target_x >= 0)
					{
						if (!world.get_tile(target_x, target_y).collision)
						{
							tile_position.setX(target_x);
						}
					}
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
