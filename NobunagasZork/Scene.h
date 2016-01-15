#ifndef __Scene__
#define __Scene__

#include <string>
#include <vector>
#include "Object.h"

using namespace std;

class Scene
{
public:
	Scene(const char* title, const string text, vector<Object> sceneObjectList);
	Scene(char* title, const string text);
	Scene();
	~Scene();
	void ConnectRooms(Scene &north, Scene &east, Scene &south, Scene &west);
	const string getDescription();
	const char* getName();
	const bool getAlarm();
	Scene* getNorth();
	Scene* getSouth();
	Scene* getWest();
	Scene* getEast();

	vector<Object> objects;

private:
	string description;
	const char* name;
	bool alarm;
	Scene *north;
	Scene *east;
	Scene *south;
	Scene *west;
};

#endif