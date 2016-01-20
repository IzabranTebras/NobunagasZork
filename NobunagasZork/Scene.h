#ifndef __Scene__
#define __Scene__

#include <string>
#include <vector>
#include "Object.h"

using namespace std;

class Scene
{
public:
	Scene(const char* title, const string text, const vector<Object*> sceneObjectList);
	Scene(char* title, const string text);
	Scene();
	~Scene();

	void ConnectRooms(Scene *north, Scene *east, Scene *south, Scene *west);
	const string getDescription() const;
	const char* getName() const;
	const bool getAlarm() const;
	Scene* getNorth() const;
	Scene* getSouth() const;
	Scene* getWest() const;
	Scene* getEast() const;

	vector<Object*> objects;

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