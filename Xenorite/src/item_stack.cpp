#include "item_stack.h"

ItemStack::ItemStack(ItemType p_type, int p_count) 
	:
	type(p_type),
	count(p_count)
{
}

ItemStack::ItemStack()
	:
	count(-1)
{
}

bool ItemStack::is_equal_type(const ItemStack & p_stack) const
{
	return this->type == p_stack.type;
}
