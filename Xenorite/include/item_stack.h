#pragma once

#include "item_type.h"

class ItemStack
{
public:
	// parameterized constructor
	ItemStack(ItemType p_type, int p_count);

	// default constructor for std::vector generating "emtpy"-state
	ItemStack();

	ItemType type;
	int count;

	// check if the ItemType of the current stack matches with the one passed
	// as argument
	bool is_equal_type(const ItemStack& p_stack) const;
};