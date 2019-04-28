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
	//for (auto p : keys)
	//	std::cout << p.first << " " << p.second << std::endl;
	if (current_tick <= 58)
	{
		current_tick++;
	}
	else
	{
		current_tick = 0;
		std::cout << " 60 Updates!" << current_tick << std::endl;
	}

	if (keys[Qt::Key_W])
	{
		current_world->m_player.update(PlayerDirection::UP);
	}
	else if (keys[Qt::Key_D])
	{
		current_world->m_player.update(PlayerDirection::RIGHT);
	}
	else if (keys[Qt::Key_S])
	{
		current_world->m_player.update(PlayerDirection::DOWN);
	}
	else if (keys[Qt::Key_A])
	{
		current_world->m_player.update(PlayerDirection::LEFT);
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

QImage& GameController::get_player_sprite(PlayerDirection dir) const
{
	return *(player_sprites.find(dir))->second;
}

World & GameController::get_world()
{
	return *current_world;
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

void GameController::update_key_press(int key_code)
{
	keys[key_code] = true;
}

void GameController::update_key_release(int key_code)
{
	keys[key_code] = false;
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

	// player images path
	std::string player_path = base_path + "player\\";

	// map storing filepaths associated with enum objects
	std::map<PlayerDirection, std::string> player_res_map;

	player_res_map.insert(std::make_pair<PlayerDirection, std::string>(
		PlayerDirection::UP, "player_up.png"
		));

	player_res_map.insert(std::make_pair<PlayerDirection, std::string>(
		PlayerDirection::RIGHT, "player_right.png"
		));

	player_res_map.insert(std::make_pair<PlayerDirection, std::string>(
		PlayerDirection::DOWN, "player_down.png"
		));

	player_res_map.insert(std::make_pair<PlayerDirection, std::string>(
		PlayerDirection::LEFT, "player_left.png"
		));

	// initialize player sprites
	for (const std::pair<PlayerDirection, std::string>& pair : player_res_map)
	{
		player_sprites.insert(std::pair<PlayerDirection, std::shared_ptr<QImage>>(
			pair.first,
			std::make_shared<QImage>(
				Texture::load_png(player_path + pair.second))
			));
	}
}
