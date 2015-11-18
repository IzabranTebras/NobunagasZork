#include "NPC.h"



NPC::NPC(char * enemyName, int life, int attackDamage, bool armoured, Scene &scene)
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

const bool NPC::getArmour()
{
	return armour;
}

const char * NPC::getName()
{
	return name;
}
