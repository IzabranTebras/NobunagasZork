#ifndef __NPC__
#define __NPC__

#include "Character.h"

class NPC :
	public Character
{
public:
	NPC(const char* enemyName, const int life, const int attackDamage, int agility, const bool armoured);
	NPC();
	~NPC();
	int Attack(Character *player);
	const bool getArmour() const;
	const char* getName() const;

private:
	bool armour;
	const char* name;
};

#endif