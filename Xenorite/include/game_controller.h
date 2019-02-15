#ifndef __GAMECONTROLLER_H__
#define __GAMECONTROLLER_H__

#include <iostream>
#include <string>

class GameController
{
public:
	GameController();

	void update();

	int get_current_tick() const;

private:
	// stores the current tick value 0 - 59
	int current_tick = 0;
};

#endif