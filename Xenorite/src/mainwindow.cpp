#include "mainwindow.h"
#include "game_controller.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	setWindowTitle("Xenorite");

	

	try {
		m_game_controller = std::make_shared<GameController>(GameController());
	}
	catch (const Simple_Message_Exception& e)
	{
		std::cerr << e.m_error_message << std::endl;
	}
	std::cout << this->width() << std::endl;
	// set initial window dimension on controller
	m_game_controller->set_window_width(this->width());
	m_game_controller->set_window_height(this->height());

	

	// pass the controller to the render widget
	ui.render_widget->set_game_controller(m_game_controller);

	// pass game_controller to render
	ui.render_widget->set_game_controller(m_game_controller);

	timer = new QTimer();

	// connect the timer for automatic mode
	connect(timer, SIGNAL(timeout()),
		this, SLOT(tick()));

	timer->start(1000 / 60);
}


void MainWindow::resizeEvent(QResizeEvent * event)
{
	std::cout << "resizing" << std::endl;
	// only update controller values if there is a world loaded 
	// TODO: this might not be necessary

	// share the new render window size with the game controlller
	m_game_controller->set_window_width(this->width());
	m_game_controller->set_window_height(this->height());
	
}

void MainWindow::tick()
{
	m_game_controller->update();

	ui.render_widget->update();
	ui.render_widget->repaint();
}
