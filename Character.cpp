#include "Character.h"

Character::Character()
{
}


Character::~Character()
{
	objects.clear();
	objects.~vector();
}

int Character::Attack()
{
	return 0;
}
