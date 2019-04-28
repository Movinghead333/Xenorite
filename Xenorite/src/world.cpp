#include "world.h"

#include <iostream>
#include <fstream>

#include "simple_message_exception.h"
#include "utility.h"

World::World(
	int p_width,
	int p_height,
	const std::vector<std::shared_ptr<BasicTile>>& p_tiles)
	:
	width(p_width),
	height(p_height),
	tiles(p_tiles),
	m_player(Player(2,2, p_width, p_height))
{
}

std::unique_ptr<World> World::load_world(const std::string & p_file_path)
{
	std::cout << "Loading World from file: " << p_file_path << std::endl;

	// open file
	std::ifstream input_file(p_file_path);

	// check if the file opened
	if (!input_file.is_open())
	{
		throw Simple_Message_Exception("File could not be opened!");
	}

	std::string current_line;
	int width, height;

	// read colony-width
	if (std::getline(input_file, current_line))
	{
		if (Utility::is_number(current_line))
		{
			width = std::stoi(current_line);
		}
		else
		{
			throw Simple_Message_Exception(
				"Invalid Argument for parameter: <width>");
		}
	}

	// read colony-height
	if (std::getline(input_file, current_line))
	{
		if (Utility::is_number(current_line))
		{
			height = std::stoi(current_line);
		}
		else
		{
			throw Simple_Message_Exception(
				"Invalid Argument for parameter: <height>");
		}
	}

	// temp vector for world object setup
	std::vector<std::shared_ptr<BasicTile>> temp_tiles;
	temp_tiles.reserve(width * height);

	// y loop reading in the lines
	for (int y_loop = 0; y_loop < height; y_loop++)
	{
		// read next line
		std::getline(input_file, current_line);
		std::cout << current_line << std::endl;

		// x loop reading in the single chars
		for (int x_loop = 0; x_loop < width; x_loop++)
		{
			char current_char = current_line[x_loop];

			temp_tiles.push_back(
				std::make_unique<BasicTile>(
				BasicTile(
					Utility::char_to_tile_type(current_char))));
		}
	}

	return std::make_unique<World>(World(width, height, temp_tiles));
}

BasicTile& World::get_tile(int x, int y)
{
	return *tiles[y * width + x];
}

int World::get_width()
{
	return width;
}

int World::get_height()
{
	return height;
}
