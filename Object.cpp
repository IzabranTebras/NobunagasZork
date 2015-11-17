#include "Object.h"

Object::Object(char* obj, int num)
{
	name = obj;
	quantity = num;
	readable = false;
	openable = false;
}

Object::Object(char* obj, int num, char* text)
{
	name = obj;
	quantity = num;
	readable = true;
	content = text;
	openable = false;
}

Object::Object(char * obj, int num, bool isOpen, vector<Object> objectsList)
{
	name = obj;
	quantity = num;
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
}
