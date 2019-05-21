#include "ore_tile.h"

OreTile::OreTile(TileType p_tiletype)
	:
	BasicTile(p_tiletype, true),
	remaining_resources(1000)
{
}
