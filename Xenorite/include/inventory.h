#pragma once

#include <vector>
#include <string>

#include "item_stack.h"

class Inventory
{
public:
	Inventory();

	~Inventory();

	void add_item(ItemStack p_stack);

	ItemStack& get_item(int x, int y);

	std::string to_string() const;

private:
	ItemStack* items;

	const int ROWS = 10;
	const int COLS = 10;
	const int MAX_INV_SIZE = ROWS * COLS;
};
