#include "Scene.h"

Scene::Scene(const string title, const string text, vector<Object> sceneObjectList)
{
	name = title;
	description = text;
	objects = sceneObjectList;
	alarm = false;
}

Scene::Scene(const string title, const string text)
{
	name = title;
	description = text;
	alarm = false;
}

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::ConnectRooms(Scene &ptrnorth, Scene &ptreast, Scene &ptrsouth, Scene &ptrwest) {
	north = &ptrnorth;
	east = &ptreast;
	south = &ptrsouth;
	west = &ptrwest;
}
