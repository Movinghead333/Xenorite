#pragma once

#include "tile_type.h"

class BasicTile
{
public:
	// basic constructor taking just the TileType of the newly constructed tile
	BasicTile(TileType p_tile_type, bool p_collision);
	BasicTile() {};

	// virtual destructor for later polymorphic use
	virtual ~BasicTile();

	// Tiles' TileType
	TileType tile_type;

	// bool for indicating collision
	// default value is false for basic groundtiles
	bool collision = false;
};
