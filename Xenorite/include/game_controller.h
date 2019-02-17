#pragma once

#include <iostream>
#include <string>
#include <map>

#include <qimage.h>

#include "texture.h"
#include "item_type.h"
#include "tile_type.h"

class GameController
{
public:
	GameController();

	void update();

	int get_current_tick() const;

	QImage& get_tile_sprite(TileType p_tile_type) const;

private:
	// stores the current tick value 0 - 59
	int current_tick = 0;

	// map storing all tile graphics with there matching enum type as key
	std::map<TileType, std::shared_ptr<QImage>> tile_sprites;

	// map storing all item graphics with there matching enum type as key
	std::map<ItemType, std::shared_ptr<QImage>> item_sprites;

	void load_textures();
};