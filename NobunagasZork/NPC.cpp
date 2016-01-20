#include "NPC.h"



NPC::NPC(const char * enemyName, const int life, const int attackDamage, const bool armoured, Scene &scene)
{
	name = enemyName;
	health = life;
	attack = attackDamage;
	armour = armoured;
	room = &scene;
}

NPC::NPC()
{
}


NPC::~NPC()
{
}

const bool NPC::getArmour() const
{
	return armour;
}

const char* NPC::getName() const
{
	return name;
}
