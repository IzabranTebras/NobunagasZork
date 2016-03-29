#ifndef __Scene__
#define __Scene__

#include <string>
#include <vector>
#include "Object.h"
#include "NPC.h"

using namespace std;

class Scene
{
public:
	Scene(char* title, const string text);
	Scene();
	~Scene();

	void ConnectRooms(Scene *north, Scene *east, Scene *south, Scene *west);
	const string getDescription() const;
	const char* getName() const;
	Scene* getNorth() const;
	Scene* getSouth() const;
	Scene* getWest() const;
	Scene* getEast() const;

	vector<Object*> objects;
	vector<NPC*> npcs;

private:
	string description;
	const char* name;
	Scene *north;
	Scene *east;
	Scene *south;
	Scene *west;
};

#endif