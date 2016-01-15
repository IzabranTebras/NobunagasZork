#include "Object.h"

Object::Object(char* obj, int num)
{
	name = obj;
	damageAttack = num;
	readable = false;
	openable = false;
}

Object::Object(char* obj, int num, char* text)
{
	name = obj;
	damageAttack = num;
	readable = true;
	content = text;
	openable = false;
}

Object::Object(char * obj, int num, bool isOpen, vector<Object> objectsList)
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

const char * Object::getName()
{
	return name;
}

const char * Object::getContent()
{
	return content;
}

const bool Object::getReadable()
{
	return readable;
}

const bool Object::getOpenable()
{
	return openable;
}

const int Object::getDamageAttack()
{
	return damageAttack;
}

const bool Object::getOpen()
{
	return open;
}

const void Object::setOpen(bool nowOpen)
{
	open = nowOpen;
}
