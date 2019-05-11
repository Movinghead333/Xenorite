#pragma once

#include "basic_tile.h"


class OreTile : public BasicTile
{
public:
	OreTile(TileType p_tiletype);

	int remaining_resources;
};