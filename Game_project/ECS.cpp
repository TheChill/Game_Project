#include "ECS.h"

void Entity::add_group(Group group)
{
	group_bit_set[group] = true;
	manager.add_to_group(this, group);
}
