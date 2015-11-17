#include "Character.h"

Character::Character(Scene & loc, vector<Object> playerList)
{
	room = &loc;
	objects = playerList;
}

Character::Character()
{
}


Character::~Character()
{
}

int Character::Attack()
{
	return 0;
}
