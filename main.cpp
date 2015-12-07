#include <iostream>
#include <conio.h>
#include "Character.h"
#include "Object.h"
#include "Player.h"
#include "NPC.h"
#include "World.h"
#include <vector>

using namespace std;

enum states
{
	GO,
	READ,
	TAKE,
	DROP,
	OPEN,
	KILL,
	THROW
};

bool InputLogic(states state, char* command, Player *player, vector<NPC> enemiesList) {
	int i;
	int j;
	char* special[2];
	bool fin = false;

	switch (state) {
	case GO:
		command = strtok(NULL, " ");
		if (command != NULL) {
			cout << player->Go(command);
		}
		break;

	case TAKE:
		command = strtok(NULL, " ");
		i = 0;
		special[i];
		while (special[i] = strtok(NULL, " ")) {
			++i;
		}
		//i = 2 -> kunai = 0, from = 1 and box = 2
		if (command != NULL) {
			if (i == 2) {
				cout << player->Take(command, special[1]);
			}
			else {
				cout << player->Take(command);
			}
		}
		else {
			cout << "I don't understand you, guy!\n\n";
		}
		break;

	case READ:
		command = strtok(NULL, " ");
		if (command != NULL) {
			cout << player->Read(command);
		}
		break;

	case DROP:
		command = strtok(NULL, " ");
		i = 0;
		special[i];
		while (special[i] = strtok(NULL, " ")) {
			++i;
		}
		//i = 2 -> kunai = 0, from = 1 and box = 2
		if (command != NULL) {
			if (i == 2) {
				cout << player->Drop(command, special[1]);
			}
			else {
				cout << player->Drop(command);
			}
		}
		else {
			cout << "I don't understand you, guy!\n\n";
		}
		break;

	case OPEN:
		command = strtok(NULL, " ");
		if (command != NULL) {
			cout << player->Open(command) + "\n";

			i = 0;
			while ((player->room->objects.size() > i) && (strcmp(player->room->objects[i].getName(), command) != 0)) {
				++i;
			}
			for (int j = 0; j < player->room->objects[i].objects.size(); ++j) {
				cout << "- " + string(player->room->objects[i].objects[j].getName()) + "\n";
			}
		}
		else {
			cout << "I don't understand you, guy!\n\n";
		}
		break;

	case KILL:
		command = strtok(NULL, " ");
		if (command != NULL) {
			//busco el enemigo que quiere atacar
			j = 0;
			while (enemiesList.size() > j) {
				if ((strcmp(enemiesList[j].getName(), command) != 0) || (strcmp(player->room->getName(), enemiesList[j].room->getName()) != 0)) {
					++j;
				}
				else {
					break;
				}
			}
			if (j < enemiesList.size()) {
				cout << player->Kill(enemiesList[j]);
				if (enemiesList[j].health < 1) {
					if (strcmp(enemiesList[j].getName(), "nobunaga") == 0) {
						fin = true;
					}
					enemiesList.erase(enemiesList.begin() + j);
				}
			}
			else {
				cout << "I don't understand you, guy!\n\n";
			}
		}
		else {
			cout << "I don't understand you, guy!\n\n";
		}
		break;

	case THROW:
		command = strtok(NULL, " ");
		i = 0;
		//busco todas las palabras de la linea
		while (special[i] = strtok(NULL, " ")) {
			++i;
		}

		if ((command != NULL) && (i == 2)) {
			//busco el enemigo que quiere atacar
			j = 0;
			while (enemiesList.size() > j) {
				if ((strcmp(enemiesList[j].getName(), special[1]) != 0) || (strcmp(player->room->getName(), enemiesList[j].room->getName()) != 0)) {
					++j;
				}
				else {
					break;
				}
			}
			if (j < enemiesList.size()) {
				cout << player->Throw(command, enemiesList[j]) + "\n";
				if (enemiesList[j].health < 1) {
					if (strcmp(enemiesList[j].getName(), "nobunaga") == 0) {
						fin = true;
					}
					enemiesList.erase(enemiesList.begin() + j);
				}
			}
			else {
				cout << "The target doesn't exist!\n\n";
			}
		}
		else {
			cout << "I don't understand you, guy!\n\n";
		}
		break;

	default:
		cout << "I don't understand you, guy!\n\n";
	}

	return fin;
}

int main() {
	bool fin = false;
	char str[200];
	char* command;
	World *world = new World();

	cout << "\n\n<--------------------------------Nobunaga's Zork------------------------------->\n\nYou're a ninja and you have a mission to acomplish. For acomplish this mission you have a kunai, two shurikens and a parchment with the details of the mission. Complete the mission with stealth!\n\n";

	world->Init();

	cout << world->player->room->getDescription() + "\n\n";

	//Game loop
	while(!fin){
		if (_kbhit() != 0)
		{
			cin.getline(str, 200);
			command = strtok(str, " ");
			if (command == NULL) {
				cout << "What you want to do?!\n\n";
			}
			else {
				if (strcmp(command, "go") == 0) {
					fin = InputLogic(GO, command, world->player, world->enemiesList);
				}
				else {
					if (strcmp(command, "read") == 0) {
						fin = InputLogic(READ, command, world->player, world->enemiesList);
					}
					else {
						if (strcmp(command, "take") == 0) {
							fin = InputLogic(TAKE, command, world->player, world->enemiesList);
						}
						else {
							if (strcmp(command, "drop") == 0) {
								fin = InputLogic(DROP, command, world->player, world->enemiesList);
							}
							else {
								if (strcmp(command, "open") == 0) {
									fin = InputLogic(OPEN, command, world->player, world->enemiesList);
								}
								else {
									if (strcmp(command, "kill") == 0) {
										fin = InputLogic(KILL, command, world->player, world->enemiesList);
									}
									else {
										if (strcmp(command, "throw") == 0) {
											fin = InputLogic(THROW, command, world->player, world->enemiesList);
										}
										else {
											cout << "I don't understand you, guy!\n\n";
										}
									}
								}
							}
						}
					}
				}
			}
		}

		if (world->player->health < 1) {
			cout << "He killed you!\n\n";
			fin = true;
		}
	}
	while (_kbhit() == 0)
	{
		if (world->player->health < 1) {
			cout << "Ooooohhh you are dead.. \nNobunaga never died , got eternal life and ended up taking care of bonsai for all eternity. ";
		}
		else {
			cout << "You killed Nobunaga, your ninja clan became famous and people of Japan later achieved peace thanks to Tokugawa daimiyo. ";
		}
		while (_kbhit() == 0) {}
	}
	return 0;
}