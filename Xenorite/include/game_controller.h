#pragma once

#include <iostream>
#include <string>
#include <map>

#include <qimage.h>

#include "texture.h"
#include "item_type.h"
#include "tile_type.h"
#include "world.h"
#include "player.h"
#include "gui_state.h"

class GameController
{
public:
	GameController();

	void update();

	int get_current_tick() const;

	QImage& get_tile_sprite(TileType p_tile_type) const;

	QImage& get_player_sprite(PlayerDirection dir) const;

	QImage& get_gui_sprite(GUI_State state) const;

	World& get_world();

	int get_window_width() const;
	int get_window_height() const;

	void set_window_width(int new_width);
	void set_window_height(int new_height);

	// return true if there is a world loaded into memory
	bool world_is_loaded() const;

	// called from render_Widget updating the keymap
	void update_key_press(int key_code);

	// called from render_Widget updating the keymap
	void update_key_release(int key_code);

	// return the current gui state
	GUI_State get_gui_state() const;



private:
	// PRIVATE MEMBERS

	// gui-state
	GUI_State gui_state = GUI_State::IN_GAME;

	// Key Map
	std::map<int, bool> keys;

	// stores the current tick value 0 - 59
	int current_tick = 0;

	// width in pixels of the mainwindow render area
	int screen_width;
	// height in pixels of the mainwindow render area
	int screen_height;

	// current world object
	std::unique_ptr<World> current_world;

	// map storing all tile graphics with there matching enum type as key
	std::map<TileType, std::shared_ptr<QImage>> tile_sprites;

	// map storing all item graphics with there matching enum type as key
	std::map<ItemType, std::shared_ptr<QImage>> item_sprites;

	// gui sprite resources
	std::map<GUI_State, std::shared_ptr<QImage>> gui_sprites;

	// player sprite
	std::map<PlayerDirection, std::shared_ptr<QImage>> player_sprites;

	// PRIVATE METHODS
	void load_textures();
};