#ifndef __World__
#define __World__
#include "Scene.h"
#include "Player.h"
#include "Object.h"
#include "NPC.h"
#include "Character.h"

class World
{
public:
	World();
	~World();
	void Init();

	vector<Scene> *scenes = new vector<Scene>();
	vector<NPC> enemiesList;
	Player *player;
};
#endif