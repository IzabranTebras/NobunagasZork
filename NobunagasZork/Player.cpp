#include "Player.h"

Player::Player(Scene *loc, vector<Object*> playerObjectsList, int life)
{
	room = loc;
	objects = playerObjectsList;
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

// Function that comproves the moves
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

// Function that comproves if an object is readable
string Player::Read(char* objName)
{
	int i = 0;
	if (objects.empty() == false) {
		while ((objects.size() > i) && (strcmp(objects[i]->getName(), objName) != 0)) {
			++i;
		}
		if (i < objects.size()) {
			if (objects[i]->getReadable() == false) {
				return "Eeeemm... What?\n\n";
			}
		}
		else {
			return "I'm sorry but i think that you don't have these object...\n\n";
		}
	}
	return string(objects[i]->getContent()) + "\n\n";
}

// Function that manages the drop of an objet into a room
string Player::Drop(char* objName)
{
	int i = 0;
	if (objects.empty() == false) {
		while ((objects.size() > i) && (strcmp(objects[i]->getName(), objName) != 0)) {
			++i;
		}
		if (i < objects.size()) {
			room->objects.push_back(objects[i]);		// The object is added to the room objects list
			objects.erase(objects.begin() + i);			// The object is removed from the objects list of the player
		}
		else {
			return "I'm sorry but you don't have that object.\n\n";
		}
	}
	return string(objName) + " dropped.\n\n";
}

// Function that manages the drop of an object into a container
string Player::Drop(char * objName, char * container)
{
	int i = 0, j = 0;

	if (room->objects.empty() == false) {
		while ((room->objects.size() > i) && (strcmp(room->objects[i]->getName(), container) != 0)) {
			++i;
		}
		if (i < room->objects.size()) {
			if (room->objects[i]->getOpen() == true) {
				while ((objects.size() > j) && (strcmp(objects[j]->getName(), objName) != 0)) {
					++j;
				}
				room->objects[i]->objects.push_back(objects[j]);		// The object is added to the container objects list
				objects.erase(objects.begin() + j);						// The object is removed from the objects list of the player
			}
			else {
				return "The object is closed.\n\n";
			}
		}
		else {
			return "I'm sorry but you don't have that object.\n\n";
		}
	}
	return string(objName) + " dropped.\n\n";
}

// Function that manages take an object of a room
string Player::Take(char * objName)
{
	int i = 0;
	if (room->objects.empty() == false) {
		while ((room->objects.size() > i) && (strcmp(room->objects[i]->getName(), objName) != 0)) {
			++i;
		}
		if (i < room->objects.size()) {
			objects.push_back(room->objects[i]);				// The object is added to the objects list of the player container objects list
			room->objects.erase(room->objects.begin() + i);		// The object is removed from the objects list of the room
		}
		else {
			return "I'm sorry but there is no object with that name here.\n\n";
		}
	}
	return string(objName) + " taken.\n\n";
}

// Function that manages take an object of a container
string Player::Take(char * objName, char * container)
{
	int i=0 ,j = 0;

	if (room->objects.empty() == false) {
		while ((room->objects.size() > i) && (strcmp(room->objects[i]->getName(), container) != 0)) {		// Search container
			++i;
		}
		if (i < room->objects.size()) {
			if (room->objects[i]->getOpen() == true) {
				while ((room->objects[i]->objects.size() > j) && (strcmp(room->objects[i]->objects[j]->getName(), objName) != 0)) {		// Search object in container
					++j;
				}
				if (strcmp(room->objects[i]->objects[j]->getName(), container) == 0) {
					objects.push_back(room->objects[i]->objects[j]);							// The object is added to the objects list of the player
					room->objects[i]->objects.erase(room->objects[i]->objects.begin() + j);		// The object is removed from container objects list
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

// Function that manages the open of a container
string Player::Open(char * objOpenable)
{
	int i = 0;

	if (room->objects.empty() == false) {
		while ((room->objects.size() > i) && (strcmp(room->objects[i]->getName(), objOpenable) != 0)) {
			++i;
		}
		if (i < room->objects.size()) {
			if (room->objects[i]->getOpenable() == true) {		// if is an openable object
				if (room->objects[i]->getOpen() == false) {		// if the object isn't open yet
					room->objects[i]->setOpen(true);
					if (room->objects[i]->objects.empty() == true) {
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

// Function that manages the throw of an object to target
string Player::Throw(char * obj, NPC *target)
{
	int i = 0;

	if (objects.empty() == false) {
		while ((objects.size() > i) && (strcmp(objects[i]->getName(), obj) != 0)) {
			++i;
		}

		if (i < objects.size()) {
			target->health -= objects[i]->getDamageAttack();		// The target take the damage of the object
			objects.erase(objects.begin() + i);						// The object is lost

			if (target->health < 1) {		// Poner que el target desaparece
				return "Enemy killed. \n\n";
			}
		}
		else {
			return "You don't have this object.\n\n";
		}
	}
	return "Enemy damaged.\n\n";
}

// Function that comproves and manages the stealth kill
string Player::Kill(NPC *enemy)
{
	if (room->getAlarm() == false) {			// Only is possible kill a enemy with stealth if the alarm is disable
		enemy->health = 0;
		return "Enemy killed.\n\n";
	}
	else {
		return "You can't kill with stealth if the guards are alert.\n\n";
	}
}
