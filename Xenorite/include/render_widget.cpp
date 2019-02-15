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
	//std::cout << "drawing frame for tick: ";
	//std::cout << m_game_controller_ref->get_current_tick() << std::endl;
}
