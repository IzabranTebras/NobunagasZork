#include "Scene.h"

Scene::Scene(const char* title, const string text, vector<Object> sceneObjectList)
{
	name = title;
	description = text;
	objects = sceneObjectList;
	alarm = false;
}

Scene::Scene(char* title, const string text)
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
	objects.clear();
	objects.~vector();
}

void Scene::ConnectRooms(Scene &ptrnorth, Scene &ptreast, Scene &ptrsouth, Scene &ptrwest) {
	north = &ptrnorth;
	east = &ptreast;
	south = &ptrsouth;
	west = &ptrwest;
}

const string Scene::getDescription()
{
	return description;
}

const char * Scene::getName()
{
	return name;
}

const bool Scene::getAlarm()
{
	return alarm;
}

Scene * Scene::getNorth()
{
	return north;
}

Scene * Scene::getSouth()
{
	return south;
}

Scene * Scene::getWest()
{
	return west;
}

Scene * Scene::getEast()
{
	return east;
}
