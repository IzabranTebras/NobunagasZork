#include "Character.h"

Character::Character()
{
}


Character::~Character()
{
	objects.clear();
	objects.~vector();
}


