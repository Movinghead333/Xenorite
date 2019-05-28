#include "render_widget.h"

#include <iostream>

#include <qpainter>
#include <qkeyevent>

RenderWidget::RenderWidget(QWidget *parent)
	: QWidget(parent)
{
	setFocusPolicy(Qt::StrongFocus);
}

void RenderWidget::set_game_controller(
	std::shared_ptr<GameController> p_game_controller)
{
	m_game_controller_ref = p_game_controller;
}

void RenderWidget::keyPressEvent(QKeyEvent *e)
{
	// skip if the controller is not there yet
	if (!m_game_controller_ref) return;
	m_game_controller_ref->update_key_press(e->key());
	//QWidget::keyPressEvent(e);
}

void RenderWidget::keyReleaseEvent(QKeyEvent * e)
{
	// skip if the controller is not there yet
	if (!m_game_controller_ref) return;
	m_game_controller_ref->update_key_release(e->key());
	//QWidget::keyPressEvent(e);
}

void RenderWidget::paintEvent(QPaintEvent * event)
{
	if (!m_game_controller_ref->world_is_loaded())
		return;

	int sprite_dim = 32;

	//std::cout << "drawing frame for tick: ";
	//std::cout << m_game_controller_ref->get_current_tick() << std::endl;
	int screen_width = m_game_controller_ref->get_window_width();
	int screen_height = m_game_controller_ref->get_window_height();
	
	World& world = m_game_controller_ref->get_world();

	// get max map dimensions for draw-area checks
	int max_x_tiles = world.get_width();
	int max_y_tiles = world.get_height();

	// amount of tiles which get rendered along x and y axis
	int x_tiles = (screen_width / 32) + 2;
	int y_tiles = (screen_height / 32) + 2;

	// player x and y coordinate in pixels
	QPoint player_pos = QPoint(((screen_width / 2) - (sprite_dim / 2)),
							   ((screen_height / 2) - (sprite_dim / 2)));

	QPoint tile_offset = QPoint((-x_tiles / 2), (-y_tiles / 2));

	// point from where the render loops start drawing the tiles
	QPoint render_origin = QPoint((player_pos.x() + (sprite_dim * tile_offset.x())),
								  (player_pos.y() + (sprite_dim * tile_offset.y())));

	// get the player's tile-position
	QPoint player_tile = world.m_player.tile_position;

	//std::cout << x_tiles / 2 << " " << std::endl;
	

	QPainter painter(this);

	// the x and y coordinates of the first tile in tile-coordinates
	QPoint tile_origin = player_tile + tile_offset;

	//std::cout << tile_origin.x() << " "  << tile_origin.y() << std::endl;



	// tile render layer
	for (int y = 0; y < y_tiles; y++)
	{
		for (int x = 0; x < x_tiles; x++)
		{
			QPoint tile_coord = tile_origin + QPoint(x, y);

			if (tile_coord.x() < 0 || tile_coord.x() >= max_x_tiles ||
				tile_coord.y() < 0 || tile_coord.y() >= max_y_tiles)
				continue;

			//std::cout << tile_coord.x() << " " << tile_coord.y() << std::endl;
			QPoint pos = render_origin;
			pos += QPoint(x * sprite_dim, y * sprite_dim);
			painter.drawImage(pos,
				m_game_controller_ref->get_tile_sprite(
					world.get_tiletype(tile_coord.x(), tile_coord.y())));
		}
	}


	// player render layer
	QPoint pos = QPoint(((screen_width  / 2) - (sprite_dim / 2)),
						((screen_height / 2) - (sprite_dim / 2)));
	painter.drawImage(player_pos, m_game_controller_ref->get_player_sprite(
		world.m_player.player_dir));


	// GUI windows layer
	switch (m_game_controller_ref->get_gui_state())
	{
	case GUI_State::INVENTORY:
		std::cout << "showing inventory" << std::endl;
		QPoint inv_pos = QPoint(screen_width / 2, screen_height / 2);
		const QImage& inv_img = m_game_controller_ref->get_gui_sprite(GUI_State::INVENTORY);
		inv_pos -= QPoint(inv_img.width() / 2, inv_img.height() / 2);
		render_inventory(painter, inv_pos.x(), inv_pos.y());
		break;
	}

}

void RenderWidget::render_inventory(QPainter & p_painter, int p_x, int p_y)
{
	QPoint offset = QPoint(4, 40);
	offset += QPoint(p_x, p_y);

	p_painter.drawImage(QPoint(p_x, p_y),
		m_game_controller_ref->get_gui_sprite(GUI_State::INVENTORY));

	World& w = m_game_controller_ref->get_world();

	for (int y = 0; y < 10; y++)
	{
		for (int x = 0; x < 10; x++)
		{
			ItemType temp = w.m_player.inventory.get_item(x, y).type;
			p_painter.drawImage(QPoint(offset.x() + x * 36, offset.y() + y * 36)
				, m_game_controller_ref->get_tile_sprite(TileType::G_XENORITE_ORE));
		}
	}
}

