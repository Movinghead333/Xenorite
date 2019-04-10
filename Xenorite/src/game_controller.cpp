#include "game_controller.h"

GameController::GameController()
{
	std::cout << "GameController created" << std::endl;

	std::cout << "Loading Images!" << std::endl;
	load_textures();

	std::cout << "Loading test map" << std::endl;
	current_world = World::load_world("saves\\test.txt");
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

QImage& GameController::get_player_sprite() const
{
	return *player_sprite;
}

int GameController::get_window_width() const
{
	return screen_width;
}

int GameController::get_window_height() const
{
	return screen_height;
}

void GameController::set_window_width(int new_width)
{
	screen_width = new_width;
}

void GameController::set_window_height(int new_height)
{
	screen_height = new_height;
}

bool GameController::world_is_loaded() const
{
	return current_world != nullptr;
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
		TileType::G_BASIC, "basic_ground.png"
		));
	
	tile_res_map.insert(std::make_pair<TileType, std::string>(
		TileType::G_XENORITE_ORE, "xenorite_ore.png"
		));

	tile_res_map.insert(std::make_pair<TileType, std::string>(
		TileType::G_KRONOMITE_ORE, "kronomite_ore.png"
		));

	tile_res_map.insert(std::make_pair<TileType, std::string>(
		TileType::G_RAW_CRYSTALITE, "raw_crystalite.png"
		));

	tile_res_map.insert(std::make_pair<TileType, std::string>(
		TileType::G_ROCK, "rock.png"
		));
	
	// initialize tile sprites
	for (const std::pair<TileType, std::string>& pair : tile_res_map)
	{
		tile_sprites.insert(std::pair<TileType, std::shared_ptr<QImage>>(
			pair.first,
			std::make_shared<QImage>(
				Texture::load_png(tiles_path + pair.second))
			));
	}

	player_sprite = std::make_shared<QImage>(Texture::load_png(
		"images\\player\\player.png"));
}
