#include "Character.h"

Character::Character(Scene &loc)
{
	room = &loc;
}

Character::Character()
{
}


Character::~Character()
{
}

string Character::Go(char* direction)
{
	if (strcmp(direction, "north")==0) {
		if (room->north != NULL) {
			room = room->north;
		}
		else {
			return "You can't see any such thing.";
		}
	}
	else {
		if (strcmp(direction, "south") == 0) {
			if (room->south != NULL) {
				room = room->south;
			}
			else {
				return "You can't see any such thing.";
			}
		}
		else {
			if (strcmp(direction, "east") == 0) {
				if (room->east != NULL) {
					room = room->east;
				}
				else {
					return "You can't see any such thing.";
				}
			}
			else {
				if (strcmp(direction, "west") == 0) {
					if (room->west != NULL) {
						room = room->west;
					}
					else {
						return "You can't see any such thing.";
					}
				}
				else {
					return "I don't understand you, guy!";
				}
			}
		}
	}

	return room->description;
}
