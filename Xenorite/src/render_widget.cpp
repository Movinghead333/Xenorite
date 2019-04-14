#include "render_widget.h"

#include <iostream>

#include <qpainter>

RenderWidget::RenderWidget(QWidget *parent)
	: QWidget(parent)
{
}

void RenderWidget::set_game_controller(
	std::shared_ptr<GameController> p_game_controller)
{
	m_game_controller_ref = p_game_controller;
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

	int x_tiles = (screen_width / 32) + 2;
	int y_tiles = (screen_height / 32) + 2;

	QPoint player_pos = QPoint(((screen_width / 2) - (sprite_dim / 2)),
							   ((screen_height / 2) - (sprite_dim / 2)));

	QPoint render_origin = QPoint((player_pos.x()  - (sprite_dim * (x_tiles / 2))),
								  (player_pos.y() - (sprite_dim * (y_tiles / 2))));

	std::cout << render_origin.x() << " " << render_origin.y() << std::endl;
	

	QPainter painter(this);

	painter.drawImage(QPoint(0, 0), m_game_controller_ref->get_tile_sprite(
		TileType::G_BASIC));

	// tile render
	for (int y = 0; y < y_tiles; y++)
		for (int x = 0; x < x_tiles; x++)
		{
			QPoint pos = render_origin;
			pos += QPoint(x * sprite_dim, y * sprite_dim);
			painter.drawImage(pos,
				m_game_controller_ref->get_tile_sprite(TileType::G_ROCK));
		}


	// player render layer
	QPoint pos = QPoint(((screen_width  / 2) - (sprite_dim / 2)),
						((screen_height / 2) - (sprite_dim / 2)));
	painter.drawImage(player_pos, m_game_controller_ref->get_player_sprite());
}

