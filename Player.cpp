#include "Player.h"

Player::Player(Scene & loc, vector<Object> playerList, int life)
{
	room = &loc;
	objects = playerList;
	health = life;
}

Player::Player()
{
}


Player::~Player()
{
	objects.clear();
	objects.~vector();
}

string Player::Go(char* direction)
{
	if (strcmp(direction, "north") == 0) {
		if (room->getNorth() != NULL) {
			room = room->getNorth();
		}
		else {
			return "You can't see any such thing.\n\n";
		}
	}
	else {
		if (strcmp(direction, "south") == 0) {
			if (room->getSouth() != NULL) {
				room = room->getSouth();
			}
			else {
				return "You can't see any such thing.\n\n";
			}
		}
		else {
			if (strcmp(direction, "east") == 0) {
				if (room->getEast() != NULL) {
					room = room->getEast();
				}
				else {
					return "You can't see any such thing.\n\n";
				}
			}
			else {
				if (strcmp(direction, "west") == 0) {
					if (room->getWest() != NULL) {
						room = room->getWest();
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

	return room->getDescription() + "\n\n";
}

string Player::Read(char* objName)
{
	int i = 0;
	if (objects.empty() == false) {
		while ((objects.size() > i) && (strcmp(objects[i].getName(), objName) != 0)) {
			++i;
		}
		if (i < objects.size()) {
			if (objects[i].getReadable() == false) {
				return "Eeeemm... What?\n\n";
			}
		}
		else {
			return "I'm sorry but i think that you don't have these object...\n\n";
		}
	}
	return string(objects[i].getContent()) + "\n\n";
}

string Player::Drop(char* objName)
{
	int i = 0;
	if (objects.empty() == false) {
		while ((objects.size() > i) && (strcmp(objects[i].getName(), objName) != 0)) {
			++i;
		}
		if (i < objects.size()) {
			room->objects.push_back(objects[i]);
			objects.erase(objects.begin() + i);
		}
		else {
			return "I'm sorry but you don't have that object.\n\n";
		}
	}
	return string(objName) + " dropped.\n\n";
}

string Player::Drop(char * objName, char * container)
{
	int i = 0, j = 0;

	if (room->objects.empty() == false) {
		while ((room->objects.size() > i) && (strcmp(room->objects[i].getName(), container) != 0)) {
			++i;
		}
		if (i < room->objects.size()) {
			if (room->objects[i].getOpen() == true) {
				while ((objects.size() > j) && (strcmp(objects[j].getName(), objName) != 0)) {
					++j;
				}
				room->objects[i].objects.push_back(objects[j]);
				objects.erase(objects.begin() + j);
			}
			else {
				return "The box is closed.\n\n";
			}
		}
		else {
			return "I'm sorry but you don't have that object.\n\n";
		}
	}
	return string(objName) + " dropped.\n\n";
}

string Player::Take(char * objName)
{
	int i = 0;
	if (room->objects.empty() == false) {
		while ((room->objects.size() > i) && (strcmp(room->objects[i].getName(), objName) != 0)) {
			++i;
		}
		if (i < room->objects.size()) {
			objects.push_back(room->objects[i]);
			room->objects.erase(room->objects.begin() + i);
		}
		else {
			return "I'm sorry but there is no object with that name here.\n\n";
		}
	}
	return string(objName) + " taken.\n\n";
}

string Player::Take(char * objName, char * container)
{
	int i=0 ,j = 0;

	if (room->objects.empty() == false) {
		while ((room->objects.size() > i) && (strcmp(room->objects[i].getName(), container) != 0)) {
			++i;
		}
		if (i < room->objects.size()) {
			if (room->objects[i].getOpen() == true) {
				while ((room->objects[i].objects.size() > j) && (strcmp(room->objects[i].objects[j].getName(), objName) != 0)) {
					++j;
				}
				if (strcmp(room->objects[i].objects[j].getName(), container) == 0) {
					objects.push_back(room->objects[i].objects[j]);
					room->objects[i].objects.erase(room->objects[i].objects.begin() + j);
				}
			}
			else {
				return "The box is closed.\n\n";
			}
		}
		else {
			return "I'm sorry but there is no object with that name here.\n\n";
		}
	}
	return string(objName) + " taken.\n\n";
}

string Player::Open(char * objOpenable)
{
	int i = 0;

	if (room->objects.empty() == false) {
		while ((room->objects.size() > i) && (strcmp(room->objects[i].getName(), objOpenable) != 0)) {
			++i;
		}
		if (i < room->objects.size()) {
			if (room->objects[i].getOpenable() == true) {
				if (room->objects[i].getOpen() == false) {
					room->objects[i].setOpen(true);
					if (room->objects[i].objects.empty() == true) {
						return "Nothing inside.\n\n";
					}
				}
				else {
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
	}
	return "Opened. Inside there are: ";
}

string Player::Throw(char * obj, NPC &target)
{
	int i = 0;

	if (objects.empty() == false) {
		while ((objects.size() > i) && (strcmp(objects[i].getName(), obj) != 0)) {
			++i;
		}

		if (i < objects.size()) {
			target.health -= objects[i].getDamageAttack();
			objects.erase(objects.begin() + i);

			if (target.health < 1) {
				return "Enemy killed. \n\n";
			}
			else {
				health = 0;
			}
		}
		else {
			return "You don't have this object.\n\n";
		}
	}
	return "Enemy damaged.\n\n";
}

string Player::Kill(NPC &enemy)
{
	if (room->getAlarm() == false) {
		enemy.health = 0;
		return "Enemy killed.\n\n";
	}
	else {
		return "You can't kill with stealth if the guards are alert.\n\n";
	}
}
