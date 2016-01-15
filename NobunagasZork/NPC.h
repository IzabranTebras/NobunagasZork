#ifndef __NPC__
#define __NPC__

#include "Character.h"
class NPC :
	public Character
{
public:
	NPC(char* enemyName, int life, int attackDamage, bool armoured, Scene &scene);
	NPC();
	~NPC();
	const bool getArmour();
	const char* getName();

private:
	bool armour;
	const char* name;
};

#endif