#include "game_controller.h"

GameController::GameController()
{
	std::cout << "GameController created" << std::endl;

	std::cout << "Loading Images!" << std::endl;
	load_textures();
}

void GameController::update()
{
	if (current_tick <= 58)
	{
		current_tick++;
	}
	else
	{
		current_tick = 0;
		std::cout << " 60 Updates!" << current_tick << std::endl;
	}
}

int GameController::get_current_tick() const
{
	return current_tick;
}

QImage& GameController::get_tile_sprite(TileType p_tile_type) const
{
	return *(tile_sprites.find(p_tile_type)->second);
}

void GameController::load_textures()
{
	// base texture path
	std::string base_path = "images\\";

	// tiles path
	std::string tiles_path = base_path + "tiles\\";

	// map storing filepaths associated with enum objects
	std::map<TileType, std::string> tile_res_map;

	tile_res_map.insert(std::make_pair<TileType, std::string>(
		TileType::G_ROCK, "rock.tga"
		));

	for (const std::pair<TileType, std::string>& pair : tile_res_map)
	{
		tile_sprites.insert(std::pair<TileType, std::shared_ptr<QImage>>(
			pair.first,
			std::make_shared<QImage>(
				Texture::load_texture(tiles_path + pair.second))
			));
	}
}
