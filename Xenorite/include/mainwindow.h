#pragma once

#include <ctime>
#include <chrono>

#include "ui_mainwindow.h"
#include "game_controller.h"
#include "simple_message_exception.h"

#include <QtWidgets/QMainWindow>
#include <qtimer.h>

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);

public slots:
	void tick();

private:
	Ui::MainWindowClass ui;

	// game controller instance
	std::shared_ptr<GameController> m_game_controller;

	// game timer
	QTimer* timer;
};
