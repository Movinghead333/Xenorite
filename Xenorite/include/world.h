#pragma once

#include <vector>
#include <memory>
#include <string>

#include "basic_tile.h"
#include "player.h"

class World
{
public:
	// constructs a world with given dimensions as well as a vector of tiles
	World(
		int p_width,
		int p_height,
		const std::vector<std::shared_ptr<BasicTile>>& p_tiles);

	static std::unique_ptr<World> load_world(const std::string& p_file_path);

	BasicTile& get_tile(int x, int y);

	int get_width();
	int get_height();

	// PUBLIC MEMBERS
	Player m_player;

private:
	// width and height in tiles
	int width;
	int height;

	// vector storing all tile object for later polymorphic use
	std::vector<std::shared_ptr<BasicTile>> tiles;
};
