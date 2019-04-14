#pragma once

#include <iostream>
#include <string>
#include <map>

#include <qimage.h>

#include "texture.h"
#include "item_type.h"
#include "tile_type.h"
#include "world.h"
#include "player.h"

class GameController
{
public:
	GameController();

	void update();

	int get_current_tick() const;

	QImage& get_tile_sprite(TileType p_tile_type) const;

	QImage& get_player_sprite() const;

	Player& get_player();

	World& get_world();

	int get_window_width() const;
	int get_window_height() const;

	void set_window_width(int new_width);
	void set_window_height(int new_height);

	// return true if there is a world loaded into memory
	bool world_is_loaded() const;

private:
	// PRIVATE MEMBERS

	// stores the current tick value 0 - 59
	int current_tick = 0;

	// width in pixels of the mainwindow render area
	int screen_width;
	// height in pixels of the mainwindow render area
	int screen_height;

	// player object
	Player player;

	// current world object
	std::unique_ptr<World> current_world;

	// map storing all tile graphics with there matching enum type as key
	std::map<TileType, std::shared_ptr<QImage>> tile_sprites;

	// map storing all item graphics with there matching enum type as key
	std::map<ItemType, std::shared_ptr<QImage>> item_sprites;

	// player sprite
	std::shared_ptr<QImage> player_sprite;

	// PRIVATE METHODS
	void load_textures();
};