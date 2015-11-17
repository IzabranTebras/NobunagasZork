#pragma once
#include <string>
#include <vector>
#include "Object.h"

using namespace std;

class Scene
{
public:
	Scene(const string title, const string text, vector<Object> sceneObjectList);
	Scene(const string title, const string text);
	Scene();
	~Scene();
	void ConnectRooms(Scene &north, Scene &east, Scene &south, Scene &west);

	string description;
	string name;
	vector<Object> objects;
	bool alarm;
	Scene *north;
	Scene *east;
	Scene *south;
	Scene *west;
};

