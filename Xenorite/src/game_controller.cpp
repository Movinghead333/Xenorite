#include "game_controller.h"

GameController::GameController()
{
	std::cout << "GameController created" << std::endl;
}

void GameController::update()
{
	if (current_tick <= 58)
	{
		current_tick++;
	}
	else
	{
		current_tick = 0;
		//std::cout << " 60 Updates!" << current_tick << std::endl;
	}
}

int GameController::get_current_tick() const
{
	return current_tick;
}
