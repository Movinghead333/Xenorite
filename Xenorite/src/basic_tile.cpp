#include "basic_tile.h"

BasicTile::BasicTile(TileType p_tile_type, bool p_collision)
	:
	tile_type(p_tile_type),
	collision(p_collision)
{
}

BasicTile::~BasicTile()
{
}
