#include "Scene.h"

Scene::Scene(char* title, const string text)
{
	name = title;
	description = text;
}

Scene::Scene()
{
}

Scene::~Scene()
{
	objects.clear();
}

void Scene::ConnectRooms(Scene *ptrnorth, Scene *ptreast, Scene *ptrsouth, Scene *ptrwest) {
	north = ptrnorth;
	east = ptreast;
	south = ptrsouth;
	west = ptrwest;
}

const string Scene::getDescription() const
{
	return description;
}

const char * Scene::getName() const
{
	return name;
}

Scene *Scene::getNorth() const
{
	return north;
}

Scene *Scene::getSouth() const
{
	return south;
}

Scene *Scene::getWest() const
{
	return west;
}

Scene *Scene::getEast() const
{
	return east;
}
