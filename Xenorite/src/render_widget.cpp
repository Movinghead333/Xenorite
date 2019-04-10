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
	//std::cout << "drawing frame for tick: ";
	//std::cout << m_game_controller_ref->get_current_tick() << std::endl;
	int screen_width = m_game_controller_ref->get_window_width();
	int screen_height = m_game_controller_ref->get_window_height();

	//std::cout << screen_width << " " << screen_height << std::endl;
	int sprite_dim = 32;

	QPainter painter(this);

	painter.drawImage(QPoint(0, 0), m_game_controller_ref->get_tile_sprite(
		TileType::G_BASIC));


	// player render layer
	QPoint pos = QPoint(((screen_width  / 2) - (sprite_dim / 2)),
						((screen_height / 2) - (sprite_dim / 2)));
	painter.drawImage(pos, m_game_controller_ref->get_player_sprite());
}

