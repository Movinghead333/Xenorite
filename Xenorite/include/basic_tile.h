#pragma once

#include "tile_type.h"

class BasicTile
{
public:
	// basic constructor taking just the TileType of the newly constructed tile
	BasicTile(TileType p_tile_type);
	BasicTile() {};

	// virtual destructor for later polymorphic use
	virtual ~BasicTile();

private:
	// Tiles' TileType
	TileType tile_type;
};
