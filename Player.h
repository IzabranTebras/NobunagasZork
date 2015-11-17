#pragma once
#include <string>
#include "Character.h"
#include "Scene.h"

class Player : public Character
{
public:
	Player(Scene &loc, vector<Object> playerList);
	Player();
	~Player();

	string Go(char* direction);
	string Read(char* objName);
	string Drop(char* objName);
	string Drop(char* objName, char* container);
	string Take(char* objName);
	string Take(char* objName, char* container);
	string Open(char* objOpenable);
};

