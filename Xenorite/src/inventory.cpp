#include "inventory.h"

//DEBUG
#include <iostream>

Inventory::Inventory()
	:
	items(std::vector<ItemStack>(100))
{
}

void Inventory::add_item(ItemStack p_stack)
{
	// iterate through all existing Itemstacks in inventory:
	// if one with a type matching the stack to be inserted than add the count
	// to that stack
	for (int i = 0; i < MAX_INV_SIZE; i++)
	{
		if (items[i].count != -1 && items[i].is_equal_type(p_stack))
		{
			items[i].count += p_stack.count;
			return;
		}
	}
	std::cout << "inserting new item" << std::endl;
	// no existing stack matches the passed itemstack's type
	// -> craete new stack
	for (int i = 0; i < MAX_INV_SIZE; i++)
	{
		if (items[i].count == -1)
		{
			items[i] = p_stack;
			return;
		}
	}
}

std::string Inventory::to_string() const
{
	std::string result = "";

	for (int i = 0; i < MAX_INV_SIZE; i++)
	{
		if (items[i].count != -1)
		{
			result +=
				"Item ID: " + std::to_string(items[i].type) +
				" Count: " + std::to_string(items[i].count) + "\n";

		}
	}

	return result;
}
