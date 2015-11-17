#pragma once
#include <string>
#include <vector>
#include "Scene.h"
#include "Object.h"

using namespace std;

class Character
{
public:
	Character(Scene &loc, vector<Object> playerList);
	Character();
	~Character();

	int Attack();

	Scene *room;
	vector<Object> objects;
};

