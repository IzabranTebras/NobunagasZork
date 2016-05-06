#include "Player.h"
#include <time.h>
#include <iostream>

Player::Player(Scene *loc, vector<Object*> playerObjectsList, int life, int agility, int damage)
{
	localization = loc;
	objects = playerObjectsList;
	health = life;
	speed = agility;
	damageAttack = damage;
}

Player::Player()
{
}


Player::~Player()
{
	objects.clear();
	objects.~vector();
}

int Player::Attack(NPC *enemy)
{
	// With armour the damage is divided
	if (enemy->getArmour()) {
		return damageAttack/2;
	}
	return damageAttack;
}

// Function that comproves the moves
string Player::Go(char* direction)
{
	if (strcmp(direction, "north") == 0) {
		if (localization->getNorth() != NULL) {
			if ((localization->npcs.size() == 0) || (smoke == true)) {
				localization = localization->getNorth();
			}
			else {
				alarm = true;
				cout << "\n\n<------------------------ BATTLE -------------------------->\n";
				return "The guards saw you!\n\nYou have to choose: 'rock', 'paper' or 'scissor'. What do you do?\n\n";
			}
		}
		else {
			return "You can't see any such thing.\n\n";
		}
	}
	else {
		if (strcmp(direction, "south") == 0) {
			if (localization->getSouth() != NULL) {
				if ((localization->npcs.size() == 0) || (smoke == true)) {
					localization = localization->getSouth();
				}
				else {
					alarm = true;
					cout << "\n\n<------------------------ BATTLE -------------------------->\n";
					return "The guards saw you!\n\nYou have to choose: 'rock', 'paper' or 'scissor'. What do you do?\n\n";
				}
			}
			else {
				return "You can't see any such thing.\n\n";
			}
		}
		else {
			if (strcmp(direction, "east") == 0) {
				if (localization->getEast() != NULL) {
					if ((localization->npcs.size() == 0) || (smoke == true)) {
						localization = localization->getEast();
					}
					else {
						alarm = true;
						cout << "\n\n<------------------------ BATTLE -------------------------->\n";
						return "The guards saw you!\n\nYou have to choose: 'rock', 'paper' or 'scissor'. What do you do?\n\n";
					}
				}
				else {
					return "You can't see any such thing.\n\n";
				}
			}
			else {
				if (strcmp(direction, "west") == 0) {
					if (localization->getWest() != NULL) {
						if ((localization->npcs.size() == 0) || (smoke == true)) {
							localization = localization->getWest();
						}
						else {
							alarm = true;
							cout << "\n\n<------------------------ BATTLE -------------------------->\n";
							return "The guards saw you!\n\nYou have to choose: 'rock', 'paper' or 'scissor'. What do you do?\n\n";
						}
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
	if ((localization->alternativeDescription.empty()) || (!localization->npcs.empty())) {
		return localization->getDescription() + "\n\n";
	}
	else {
		return localization->alternativeDescription + "\n\n";
	}
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
	return string(objects[i]->getLecture()) + "\n\n";
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
			localization->objects.push_back(objects[i]);		// The object is added to the room objects list
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

	if (localization->objects.empty() == false) {
		while ((localization->objects.size() > i) && (strcmp(localization->objects[i]->getName(), container) != 0)) {
			++i;
		}
		if (i < localization->objects.size()) {
			if (localization->objects[i]->getOpen() == true) {
				while ((objects.size() > j) && (strcmp(objects[j]->getName(), objName) != 0)) {
					++j;
				}
				localization->objects[i]->objects.push_back(objects[j]);		// The object is added to the container objects list
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
	if (localization->objects.empty() == false) {
		while ((localization->objects.size() > i) && (strcmp(localization->objects[i]->getName(), objName) != 0)) {
			++i;
		}

		if (i < localization->objects.size()) {
			objects.push_back(localization->objects[i]);				// The object is added to the objects list of the player container objects list
			localization->objects.erase(localization->objects.begin() + i);		// The object is removed from the objects list of the room

			if (strcmp("katana", objName) == 0) {
				damageAttack = objects[objects.size()]->getDamageAttack();
				return "You obtained Masamune! With this katana your damaged increased greatly.\n\n";
			}
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
	int i = 0, j = 0;

	if (localization->objects.empty() == false) {
		while ((localization->objects.size() > i) && (strcmp(localization->objects[i]->getName(), container) != 0)) {		// Search container
			++i;
		}
		if (i < localization->objects.size()) {
			if (localization->objects[i]->getOpen() == true) {
				while ((localization->objects[i]->objects.size() > j) && (strcmp(localization->objects[i]->objects[j]->getName(), objName) != 0)) {		// Search object in container
					++j;
				}
				if (j < localization->objects[i]->objects.size()) {
					if (strcmp(localization->objects[i]->objects[j]->getName(), container) == 0) {
						objects.push_back(localization->objects[i]->objects[j]);							// The object is added to the objects list of the player
						localization->objects[i]->objects.erase(localization->objects[i]->objects.begin() + j);		// The object is removed from container objects list
					}
				}
				else {
					return "I'm sorry but there is no object inside this container with that name.\n\n";
				}
			}
			else {
				return "The box is closed.\n\n";
			}
		}
		else {
			return "I'm sorry but there is no object container with that name here.\n\n";
		}
	}
	return string(objName) + " taken.\n\n";
}

// Function that manages the open of a container
string Player::Open(char * objOpenable)
{
	int i = 0;

	if (localization->objects.empty() == false) {
		while ((localization->objects.size() > i) && (strcmp(localization->objects[i]->getName(), objOpenable) != 0)) {
			++i;
		}
		if (i < localization->objects.size()) {
			if (localization->objects[i]->getOpenable() == true) {		// if is an openable object
				if (localization->objects[i]->getOpen() == false) {		// if the object isn't open yet
					localization->objects[i]->setOpen(true);
					if (localization->objects[i]->objects.empty() == true) {
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
			alarm = true;
			if (strcmp("smoke", obj) == 0){
				alarm = false;
				smoke = true;
				return "Enemies are stunt.\n\n";
			}

			if (strcmp("carp", obj) == 0) {
				return "The carp exploded and killed the enemy!! \n\n";
			}

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
	if (alarm == false) {			// Only is possible kill a enemy with stealth if the alarm is disable
		enemy->health = 0;
		if ((localization->npcs.size() != 0) && (smoke == false)) {
			alarm = true;
			cout << "\nEnemy killed.";
			cout << "\n\n<------------------------ BATTLE -------------------------->\n";
			return "The guards saw you!\n\nYou have to choose: 'rock', 'paper' or 'scissor'. What do you do?\n\n";
		}
		else {
			if (localization->npcs.size() == 1) {
				cout << "All the enemies are down. The alarm is off.\n";
			}
		}
		return "Enemy killed.\n\n";
	}
	else {
		return "You can't kill with stealth if the guards are alert.\n\n";
	}
}
