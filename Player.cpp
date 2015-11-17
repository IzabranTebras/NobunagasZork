#include "Player.h"


Player::Player(Scene & loc, vector<Object> playerList)
{
	room = &loc;
	objects = playerList;
}

Player::Player()
{
}


Player::~Player()
{
}

string Player::Go(char* direction)
{
	if (strcmp(direction, "north") == 0) {
		if (room->north != NULL) {
			room = room->north;
		}
		else {
			return "You can't see any such thing.\n\n";
		}
	}
	else {
		if (strcmp(direction, "south") == 0) {
			if (room->south != NULL) {
				room = room->south;
			}
			else {
				return "You can't see any such thing.\n\n";
			}
		}
		else {
			if (strcmp(direction, "east") == 0) {
				if (room->east != NULL) {
					room = room->east;
				}
				else {
					return "You can't see any such thing.\n\n";
				}
			}
			else {
				if (strcmp(direction, "west") == 0) {
					if (room->west != NULL) {
						room = room->west;
					}
					else {
						return "You can't see any such thing.\n\n";
					}
				}
				else {
					return "I don't understand you, guy!\n\n";
				}
			}
		}
	}

	return room->description;
}

string Player::Read(char* objName)
{
	int i = 0;

	while ((objects.capacity() > i) && (strcmp(objects[i].name, objName) != 0)) {
		++i;
	}
	if (strcmp(objects[i].name, objName) == 0) {
		if (objects[i].readable == false) {
			return "I'm sorry but i think that this object isn't readable...\n\n";
		}
	}
	else {
		return "Eeeemm... What?\n\n";
	}
	return objects[i].content;
}

string Player::Drop(char* objName)
{
	int i = 0;

	while ((objects.capacity() > i) && (strcmp(objects[i].name, objName) != 0)) {
		++i;
	}
	if (strcmp(objects[i].name, objName) == 0) {
		room->objects.push_back(objects[i]);
		objects.erase(objects.begin() + i);
	}
	else {
		return "I'm sorry but you don't have that object.\n\n";
	}
	return objName;
}

string Player::Drop(char * objName, char * container)
{
	int i = 0, j = 0;

	while ((room->objects.capacity() > i) && (strcmp(room->objects[i].name, container) != 0)) {
		++i;
	}
	if (strcmp(room->objects[i].name, container) == 0) {
		while ((objects.capacity() > j) && (strcmp(objects[j].name, objName) != 0)) {
			++j;
		}
		room->objects[i].objects.push_back(objects[j]);
		objects.erase(objects.begin() + j);
	}
	else {
		return "I'm sorry but you don't have that object.\n\n";
	}
	return objName;
}

string Player::Take(char * objName)
{
	int i = 0;

	while ((room->objects.capacity() > i) && (strcmp(room->objects[i].name, objName) != 0)) {
		++i;
	}
	if (strcmp(room->objects[i].name, objName) == 0) {
		objects.push_back(room->objects[i]);
		room->objects.erase(room->objects.begin() + i);
	}
	else {
		return "I'm sorry but there is no object with that name here.\n\n";
	}
	return objName;
}

string Player::Take(char * objName, char * container)
{
	int i=0 ,j = 0;

	while ((room->objects.capacity() > i) && (strcmp(room->objects[i].name, container) != 0)) {
		++i;
	}
	if (strcmp(room->objects[i].name, container) == 0) {
		while ((room->objects[i].objects.capacity() > j) && (strcmp(room->objects[i].objects[j].name, objName) != 0)) {
			++j;
		}
		if (strcmp(room->objects[i].objects[j].name, container) == 0) {
			objects.push_back(room->objects[i].objects[j]);
			room->objects[i].objects.erase(room->objects[i].objects.begin() + j);
		}
	}
	else {
		return "I'm sorry but there is no object with that name here.\n\n";
	}
	return objName;
}

string Player::Open(char * objOpenable)
{
	int i = 0;

	while ((room->objects.capacity() > i) && (strcmp(room->objects[i].name, objOpenable) != 0)) {
		++i;
	}
	if (strcmp(room->objects[i].name, objOpenable) == 0) {
		if (room->objects[i].openable == true) {
			if (room->objects[i].open == false) {
				room->objects[i].open = true;
				if (room->objects[i].objects.empty() == true) {
					return "Nothing inside.";
				}
			}else {
				return "This object is open.\n\n";
			}
		}
		else {
			return "This object can't open.\n\n";
		}
	}
	else {
		return "I'm sorry but there is no object with that name here.\n\n";
	}
	return "Inside there are: ";
}
