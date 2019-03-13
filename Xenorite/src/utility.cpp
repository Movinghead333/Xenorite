#include "utility.h"

bool Utility::is_number(const std::string& s)
{
	std::string::const_iterator it = s.begin();
	while (it != s.end() && isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}

TileType Utility::char_to_tile_type(const char & p_input_char)
{
	switch (p_input_char)
	{
	case 'a': return TileType::G_BASIC;
		break;
	case 'b': return TileType::G_XENORITE_ORE;
		break;
	case 'c': return TileType::G_KRONOMITE_ORE;
		break;
	case 'd': return TileType::G_RAW_CRYSTALITE;
		break;
	case 'e': return TileType::G_BASIC;
		break;
	}
}
