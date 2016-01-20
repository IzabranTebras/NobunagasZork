#ifndef __Character__
#define __Character__

#include <string>
#include <vector>
#include "Scene.h"
#include "Object.h"

using namespace std;

class Character
{
public:
	Character();
	~Character();
	int Attack();

	vector<Object*> objects;
	Scene *room;
	int health;
	int attack;
};

#endif