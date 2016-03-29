#include "Object.h"

Object::Object(const char* obj, const int num)
{
	name = obj;
	damageAttack = num;
	readable = false;
	openable = false;
}

Object::Object(const char* obj, const int num, const char* text)
{
	name = obj;
	damageAttack = num;
	readable = true;
	lecture = text;
	openable = false;
}

Object::Object(const char * obj, const int num, const bool isOpen, const vector<Object*> objectsList)
{
	name = obj;
	damageAttack = num;
	readable = false;
	openable = true;
	open = isOpen;
	objects = objectsList;
}

Object::Object()
{
}


Object::~Object()
{
	objects.clear();
	objects.~vector();
}

const char* Object::getName() const
{
	return name;
}

const char* Object::getLecture() const
{
	return lecture;
}

const bool Object::getReadable() const
{
	return readable;
}

const bool Object::getOpenable() const
{
	return openable;
}

const int Object::getDamageAttack() const
{
	return damageAttack;
}

const bool Object::getOpen() const
{
	return open;
}

const void Object::setOpen(bool nowOpen)
{
	open = nowOpen;
}
