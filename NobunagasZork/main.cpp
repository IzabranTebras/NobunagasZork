#include <iostream>
#include <conio.h>
#include "Character.h"
#include "Object.h"
#include "NPC.h"
#include "Player.h"
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
	THROW,
	TALK
};

bool Input(states state, char* command, Player *player) {
	int i;
	int j;
	char* special[2];
	const int MAX = 2;
	bool fin = false;

	switch (state) {
	case GO:
		command = strtok(NULL, " ");
		if (command != NULL) {
			cout << player->Go(command);
			player->smoke = false;
		}
		break;

	case TAKE:
		command = strtok(NULL, " ");
		i = 0;
		while ((i<MAX) && (special[i] = strtok(NULL, " "))) {
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
		while ((i<MAX) && (special[i] = strtok(NULL, " "))) {
			++i;
		}
		//i = 2 -> kunai = 0, to = 1 and box = 2
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
			while ((player->localization->objects.size() > i) && (strcmp(player->localization->objects[i]->getName(), command) != 0)) {
				++i;
			}
			for (int j = 0; j < player->localization->objects[i]->objects.size(); ++j) {
				cout << "- " + string(player->localization->objects[i]->objects[j]->getName()) + "\n";
			}
		}
		else {
			cout << "I don't understand you, guy!\n\n";
		}
		break;

	case KILL:
		command = strtok(NULL, " ");
		if (command != NULL) {

			// We search the enemy that we would kill
			j = 0;
			while (player->localization->npcs.size() > j) {
				if (strcmp(player->localization->npcs[j]->getName(), command) != 0) {
					++j;
				}
				else {
					break;
				}
			}
			if (j < player->localization->npcs.size()) {
				if (strcmp(player->localization->npcs[j]->getName(), "geisha") == 0)
				{
					cout << "WHAT ARE YOU TRYING TO DO!!?\n\n";
				}
				else
				{
					cout << player->Kill(player->localization->npcs[j]);
					if (player->localization->npcs[j]->health < 1) {
						if (strcmp(player->localization->npcs[j]->getName(), "nobunaga") == 0) {
							fin = true;
						}
						player->localization->npcs.erase(player->localization->npcs.begin() + j);
					}
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
		// We search all the words of a string
		while ((i<MAX) && (special[i] = strtok(NULL, " "))) {
			++i;
		}

		if ((command != NULL) && (i == 2)) {
			// We search the enemy that we would attack
			j = 0;
			while (player->localization->npcs.size() > j) {
				if (strcmp(player->localization->npcs[j]->getName(), special[1]) != 0) {
					++j;
				}
				else {
					break;
				}
			}
			if (j < player->localization->npcs.size()) 
			{
				if (strcmp(player->localization->npcs[j]->getName(), "geisha") == 0)
				{
					cout << "WHAT ARE YOU TRYING TO DO!!?\n\n";
				}
				else
				{
					cout << player->Throw(command, player->localization->npcs[j]) + "\n";
					if (player->localization->npcs[j]->health < 1) 
					{
						if (strcmp(player->localization->npcs[j]->getName(), "nobunaga") == 0) 
						{
							fin = true;
						}
						player->localization->npcs.erase(player->localization->npcs.begin() + j);
					}
					else {
						player->alarm = true;
						cout << "\n\n<------------------------ BATTLE -------------------------->\n";
						return "The guards saw you!\n\nYou have to choose: 'rock', 'paper' or 'scissor'. If you want escape and you have smoke bombs use 'smoke'. What do you do?\n\n";
					}
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

	case TALK:
		command = strtok(NULL, " ");
		if (command != NULL) {
			if ((strcmp(command, "nobunaga") == 0) || (strcmp(command, "geisha") == 0))
			{
				cout << player->Talk(command);
				if (strcmp(command, "nobunaga") == 0) {
					player->alarm = true;
					cout << "\n\n<------------------------ BATTLE -------------------------->\n";
					return "The guards saw you!\n\nYou have to choose: 'rock', 'paper' or 'scissor'. If you want escape and you have smoke bombs use 'smoke'. What do you do?\n\n";
				}
				else {
					player->kaguya = true;
				}
			}
			else
			{
				cout << "You bastard, come here!!\n";
				player->alarm = true;
				cout << "\n\n<------------------------ BATTLE -------------------------->\n";
				return "The guards saw you!\n\nYou have to choose: 'rock', 'paper' or 'scissor'. If you want escape and you have smoke bombs use 'smoke'. What do you do?\n\n";

			}
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

	cout << world->player->localization->getDescription() + "\n\n";

	//Game loop
	while(!fin){
		if (_kbhit() != 0)
		{
			cin.getline(str, 200);
			command = strtok(str, " ");
			if (world->player->alarm == false) {
				if (command == NULL) {
					cout << "What do you want to do?!\n\n";
				}
				else {
					if (strcmp(command, "go") == 0) {
						fin = Input(GO, command, world->player);
					}
					else {
						if (strcmp(command, "read") == 0) {
							fin = Input(READ, command, world->player);
						}
						else {
							if (strcmp(command, "take") == 0) {
								fin = Input(TAKE, command, world->player);
							}
							else {
								if (strcmp(command, "drop") == 0) {
									fin = Input(DROP, command, world->player);
								}
								else {
									if (strcmp(command, "open") == 0) {
										fin = Input(OPEN, command, world->player);
									}
									else {
										if (strcmp(command, "kill") == 0) {
											fin = Input(KILL, command, world->player);
										}
										else {
											if (strcmp(command, "throw") == 0) {
												fin = Input(THROW, command, world->player);
											}
											else {
												if (strcmp(command, "talk") == 0)
												{
													fin = Input(TALK, command, world->player);
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
			}
			else {
				char* election;	
				switch (rand() % 3) // 0 -> rock, 1 -> paper, 2 -> scissor
				{
				case 0:
					election = "rock";
					break;
				case 1:
					election = "paper";
					break;
				case 2:
					election = "scissor";
					break;
				}

				if ((command == NULL) || ((strcmp(command, "rock") != 0) && (strcmp(command, "paper") != 0) && (strcmp(command, "scissor") != 0) && (strcmp(command, "smoke") != 0))) {
					cout << "What do you choose?!\n\n";
				}
				else {
					if (strcmp(command, "smoke") != 0) {
						printf("\nHe choose %s and you choose %s \n", election, command);

						if (strcmp(command, election) == 0) {
							printf("DRAW!!\n\n");
							printf("Your health: %d \n", world->player->health);
							printf("Enemy health: %d \n\n", world->player->localization->npcs[0]->health);
							printf("You have to choose: 'rock', 'paper' or 'scissor'. If you want escape and you have smoke bombs use 'smoke'. What do you do?\n\n");
						}
						else {
							int attack;

							// We comprove if the player wins against the enemy
							if (((strcmp(command, "rock") == 0) && (strcmp(election, "scissor") == 0)) || ((strcmp(command, "paper") == 0) && (strcmp(election, "rock") == 0)) || ((strcmp(command, "scissor") == 0) && (strcmp(election, "paper") == 0))) {
								attack = world->player->Attack(world->player->localization->npcs[0]);
								world->player->localization->npcs[0]->health -= attack;
								printf("HIT %d \n\n", attack);
								printf("Your health: %d \n", world->player->health);

								// We delete the pointer and remove it from vector
								if (world->player->localization->npcs[0]->health < 1) {
									printf("Enemy health: 0\n\n");
									delete (world->player->localization->npcs[0]);
									world->player->localization->npcs.erase(world->player->localization->npcs.begin());
									printf("NICE! You knock out the enemy!\n");

									int i = 0;
									int j = 0;
									while (world->player->localization->npcs.size() > j) {
										if (strcmp(world->player->localization->npcs[j]->getName(), "geisha") != 0)
										{
											++i;
										}
										++j;
									}
									// When all the enemies in the zone are dead the alarm disappears
									if (world->player->localization->npcs.empty() || i == 0) {
										printf("All the enemies are down. The alarm is off.\n\n");
										world->player->alarm = false;
										printf(world->player->localization->alternativeDescription.c_str());
									}
									else {
										printf("Next enemy health: %d \n\n", world->player->localization->npcs[0]->health);
									}
								}
								else {
									printf("Enemy health: %d \n\n", world->player->localization->npcs[0]->health);
									printf("You have to choose: 'rock', 'paper' or 'scissor'. If you want escape and you have smoke bombs use 'smoke'. What do you do?\n\n");
								}
							}
							else {
								attack = world->player->localization->npcs[0]->Attack(world->player);
								world->player->health -= attack;
								if (world->player->health < 0) {
									world->player->health = 0;
								}
								printf("HIT %d \n\n", attack);
								printf("Your health: %d \n", world->player->health);
								printf("Enemy health: %d \n\n", world->player->localization->npcs[0]->health);
							}
						}
					}
					else {
						world->player->alarm = false;
						world->player->smoke = true;
						cout << "Enemies are stunt.\n\n";
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
			if (!world->player->kaguya) {
				cout << "Ooooohhh you are dead.. \nNobunaga never died , got eternal life and ended up taking care of bonsai for all eternity. ";
			}
			else {
				cout << "Ooooohhh you are dead.. \nBut Nobunaga was killed too by Kaguya. Kaguya, who came through the stars, save the world with his powers and change it.";
			}
		}
		else {
			cout << "You killed Nobunaga, your ninja clan became famous and people of Japan later achieved peace thanks to Tokugawa daimiyo. ";
		}
		while (_kbhit() == 0) {}
	}
	return 0;
}