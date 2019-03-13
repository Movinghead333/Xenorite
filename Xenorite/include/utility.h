#pragma once

#include <string>

#include "tile_type.h"

class Utility
{
public:
	// checks wether a string can be converted to a number
	static bool is_number(const std::string& s);

	static TileType char_to_tile_type(const char& p_input_char);
};
