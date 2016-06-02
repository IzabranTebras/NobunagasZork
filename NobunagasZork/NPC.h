#ifndef __NPC__
#define __NPC__

#include "Character.h"

class NPC :
	public Character
{
public:
	NPC(const char* enemyName, const int life, const int attackDamage, int agility, const bool armoured, string conversation);
	NPC();
	~NPC();
	int Attack(Character *player);
	const bool getArmour() const;
	const char* getName() const;
	const string getConversation() const;

private:
	bool armour;
	const char* name;
	string conversation;
};

#endif