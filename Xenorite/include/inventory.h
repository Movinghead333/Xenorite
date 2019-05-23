#pragma once

#include <vector>
#include <string>

#include "item_stack.h"

class Inventory
{
public:
	Inventory();

	void add_item(ItemStack p_stack);

	std::string to_string() const;

private:
	std::vector<ItemStack> items;

	const int MAX_INV_SIZE = 100;
};
