#include "mainwindow.h"
#include "game_controller.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	setWindowTitle("Xenorite");

	timer = new QTimer();

	try {
		m_game_controller = std::make_shared<GameController>(GameController());
	}
	catch (const Simple_Message_Exception& e)
	{
		std::cerr << e.m_error_message << std::endl;
	}

	// pass game_controller to render
	ui.render_widget->set_game_controller(m_game_controller);

	// connect the timer for automatic mode
	connect(timer, SIGNAL(timeout()),
		this, SLOT(tick()));

	timer->start(1000 / 60);
}

void MainWindow::tick()
{
	m_game_controller->update();

	ui.render_widget->update();
}
