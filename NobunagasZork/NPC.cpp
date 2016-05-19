#include "NPC.h"
#include <time.h>



NPC::NPC(const char *enemyName, const int life, const int attackDamage, int agility, const bool armoured)
{
	name = enemyName;
	health = life;
	damageAttack = attackDamage;
	armour = armoured;
	speed = agility;
}

NPC::NPC()
{
}


NPC::~NPC()
{
}

int NPC::Attack(Character *player)
{
	int random;
	int playerSpeed;

	// Initialize seed
	srand(time(NULL));

	// A little random speed to a certain hit random
	playerSpeed = rand() % player->speed + 1;

	if (playerSpeed <= speed) {

		// We add a random element to damage
		random = rand() % damageAttack + 1;
		return random;
	}
	printf("You avoid the attack!!\n");
	printf("You have to choose: 'rock', 'paper' or 'scissor'. What do you do?\n\n");
	return 0;
}

const bool NPC::getArmour() const
{
	return armour;
}

const char* NPC::getName() const
{
	return name;
}
