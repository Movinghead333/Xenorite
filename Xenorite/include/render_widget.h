#pragma once

#include <QWidget>

#include <game_controller.h>

class RenderWidget : public QWidget
{
	Q_OBJECT

public:
	RenderWidget(QWidget *parent = 0);

	void set_game_controller(
		std::shared_ptr<GameController> p_game_controller);

	void keyPressEvent(QKeyEvent *e) override;
	void keyReleaseEvent(QKeyEvent *e) override;

private:

	// instance of GameController
	std::shared_ptr<GameController> m_game_controller_ref;

	void paintEvent(QPaintEvent *event) override;

	void render_inventory(QPainter& p_painter, int p_x, int p_y);

	
};