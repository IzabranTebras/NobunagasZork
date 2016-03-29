#ifndef __Character__
#define __Character__

#include <vector>
#include "Object.h"

using namespace std;

class Character
{
public:
	Character();
	~Character();

	vector<Object*> objects;
	int speed;
	int health;
	int damageAttack;
};

#endif