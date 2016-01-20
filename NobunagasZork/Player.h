#ifndef __Player__
#define __Player__

#include <string>
#include "NPC.h"
#include "Character.h"
#include "Scene.h"

class Player : public Character
{
public:
	Player(Scene *loc, vector<Object*> playerObjectsList, int life);
	Player();
	~Player();

	string Go(char* direction);
	string Read(char* objName);
	string Drop(char* objName);
	string Drop(char* objName, char* container);
	string Take(char* objName);
	string Take(char* objName, char* container);
	string Open(char* objOpenable);
	string Throw(char* obj, NPC *target);
	string Kill(NPC *enemy);
};

#endif