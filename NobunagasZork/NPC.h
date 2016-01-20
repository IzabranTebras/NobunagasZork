#ifndef __NPC__
#define __NPC__

#include "Character.h"
class NPC :
	public Character
{
public:
	NPC(const char* enemyName, const int life, const int attackDamage, const bool armoured, Scene &scene);
	NPC();
	~NPC();
	const bool getArmour() const;
	const char* getName() const;

private:
	bool armour;
	const char* name;
};

#endif