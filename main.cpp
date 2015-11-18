#include <iostream>
#include <conio.h>
#include "Character.h"
#include "Object.h"
#include "Player.h"
#include "NPC.h"
#include <vector>

using namespace std;

int main() {
	bool fin = false;
	char str[200];
	char* command;
	char* special[2];
	int i,j;
	NPC *enemy;

	cout << "\n\n<--------------------------------Nobunaga's Zork------------------------------->\n\nYou're a ninja and you have a mission to acomplish. For acomplish this mission you have a kunai, two shurikens and a parchment with the details of the mission. Complete the mission with stealth!\n\n";

	//Initialize objects and list of objects for Scene
	Object parchment = Object("parchment", 1, "Your mission is kill the damiyo Nobunaga Oda. The damiyo is in Himeji castle for the next two nights.\nThe perfect moment to kill him is the night JUne 21, because the next day the damiyo recive a visit and there will be more guards.\nArchie\n\n");
	Object carp = Object("carp", 1);
	Object kunai = Object("kunai", 2);
	Object shuriken = Object("shuriken", 2);
	Object katana = Object("katana", 5);

	vector<Object> objList;
	objList.push_back(kunai);
	Object box = Object("box", 1, false, objList);

	//Initialize the rooms
	objList.clear();
	objList.push_back(box);

	Scene pb1 = Scene("PB1", "\nWest of Himeji castle\nYou are in the garden of Himeji castle. You can see some trees and walls to North and West.\n\n", objList);
	Scene pb2 = Scene("PB2", "\nSouth-West of Himeji castle\nYou are in the garden of Himeji castle. You can see more trees and walls to South and East. Seems that nobody is guarding.\n\n");
	Scene pb3 = Scene("PB3", "\nSouth of Himeji castle\nYou can see a guard without armour in the stairs to the castle door (North). He can't see you because you are hiding behind a tree. To South you can see the wall door closed, to East you can hear somelike water flowing and to West you can see some trees.\n\n");
	objList.clear();
	objList.push_back(carp);
	Scene pb4 = Scene("PB4", "\nSouth-East of Himeji castle\nYou can see a river with a red carp. To West you can see the entry of the castle, to North you can hear a little waterfall and East and South have walls.\n\n", objList);
	Scene pb5 = Scene("PB5", "\nEast of Himeji castle\nYou can see a little waterfall with a little lake, tipical Japanese garden. To South the lake advance in a river form. North, East and West are walls. A centinel is warching the river.\n\n");
	objList.clear();
	objList.push_back(box);
	Scene pb6 = Scene("PB6", "\nInside the castle\nYou can see four columns in the center of the hall. Seems that any guard are guarding the room. To East and West you can see stairs to the up floor. To South is the main entrance of the castle and in the north you can see a box.\n\n", objList);
	Scene p11 = Scene("P11", "\nFirst floor hall\nYou can see four columns in the center of the hall. To East and West you can see stairs to the entrance of castle, to North you can see stairs to second floor and to South you can see a door.\n\n");
	objList.clear();
	objList.push_back(katana);
	Scene p12 = Scene("P12", "\nFirst floor room\nYou can see a katana in the floor and a samurai backwards.\n\n", objList);
	Scene p21 = Scene("P21", "\nSecond floor hall\nYou can see a samurai guarding a door to West.\n\n");
	Scene p22 = Scene("P22", "\nRoom of the damiyo Nobunaga\nNobunaga is facing away from you, looking at the stars through the balcony.\n\n");

	//Connecting the rooms
	Scene *ptrs = &pb2;
	Scene *ptrn = NULL;
	Scene *ptre = NULL;
	Scene *ptrw = NULL;
	pb1.ConnectRooms(*ptrn, *ptre, *ptrs, *ptrw);

	ptrs = NULL;
	ptrn = &pb1;
	ptre = &pb3;
	ptrw = NULL;
	pb2.ConnectRooms(*ptrn, *ptre, *ptrs, *ptrw);

	ptrs = NULL;
	ptrn = &pb6;
	ptre = &pb4;
	ptrw = &pb2;
	pb3.ConnectRooms(*ptrn, *ptre, *ptrs, *ptrw);

	ptrs = NULL;
	ptrn = &pb5;
	ptre = NULL;
	ptrw = &pb3;
	pb4.ConnectRooms(*ptrn, *ptre, *ptrs, *ptrw);

	ptrs = &pb4;
	ptrn = NULL;
	ptre = NULL;
	ptrw = NULL;
	pb5.ConnectRooms(*ptrn, *ptre, *ptrs, *ptrw);

	ptrs = &pb3;
	ptrn = NULL;
	ptre = &p11;
	ptrw = &p11;
	pb6.ConnectRooms(*ptrn, *ptre, *ptrs, *ptrw);

	ptrs = &p12;
	ptrn = &p21;
	ptre = &pb6;
	ptrw = &pb6;
	p11.ConnectRooms(*ptrn, *ptre, *ptrs, *ptrw);

	ptrs = NULL;
	ptrn = &p11;
	ptre = NULL;
	ptrw = NULL;
	p12.ConnectRooms(*ptrn, *ptre, *ptrs, *ptrw);

	ptrs = NULL;
	ptrn = &p11;
	ptre = NULL;
	ptrw = &p22;
	p21.ConnectRooms(*ptrn, *ptre, *ptrs, *ptrw);

	ptrs = NULL;
	ptrn = NULL;
	ptre = &p21;
	ptrw = NULL;
	p22.ConnectRooms(*ptrn, *ptre, *ptrs, *ptrw);

	//Initialize characters
	Scene *ptrChar = &pb1;
	objList.clear();
	objList.push_back(parchment);
	objList.push_back(kunai);
	objList.push_back(shuriken);
	objList.push_back(shuriken);
	Player player = Player(*ptrChar, objList, 5);

	ptrChar = &pb3;
	NPC guard = NPC("guard", 3, 1, false, *ptrChar);
	ptrChar = &pb5;
	NPC guard2 = NPC("guard", 3, 1, true, *ptrChar);
	ptrChar = &p12;
	NPC samurai = NPC("samurai", 5, 3, true, *ptrChar);
	ptrChar = &p21;
	NPC samurai2 = NPC("samurai", 5, 3, true, *ptrChar);
	ptrChar = &p22;
	NPC nobunaga = NPC("nobunaga", 5, 5, false, *ptrChar);

	vector<NPC> enemiesList;
	enemiesList.push_back(guard);
	enemiesList.push_back(guard2);
	enemiesList.push_back(samurai);

	enemiesList.push_back(nobunaga);

	cout << player.room->getDescription() + "\n\n";

	//Game loop
	while(!fin){
		if (_kbhit() != 0)
		{
			cin.getline(str, 200);
			command = strtok(str, " ");
			if (command == NULL) {
				command = " ";
			}
			if (strcmp(command, "go") == 0) {
				command = strtok(NULL, " ");
				if (command != NULL) {
					cout << player.Go(command);
				}
			}
			else {
				if (strcmp(command, "read") == 0) {
					command = strtok(NULL, " ");
					if (command != NULL) {
						cout << player.Read(command);
					}
				}else {
					if (strcmp(command, "take") == 0) {
						command = strtok(NULL, " ");
						i = 0;
						special[i];
						while (special[i] = strtok(NULL, " ")) {
							++i;
						}
						//i = 2 -> kunai = 0, from = 1 and box = 2
						if (command != NULL) {
							if (i == 2) {
								cout << player.Take(command, special[1]);
							}
							else {
								cout << player.Take(command);
							}
						}else {
							cout << "I don't understand you, guy!\n\n";
						}
					}else {
						if (strcmp(command, "drop") == 0) {
							command = strtok(NULL, " ");
							i = 0;
							special[i];
							while (special[i] = strtok(NULL, " ")) {
								++i;
							}
							//i = 2 -> kunai = 0, from = 1 and box = 2
							if (command != NULL) {
								if (i == 2) {
									cout << player.Drop(command, special[1]);
								}
								else {
									cout << player.Drop(command);
								}
							}
							else {
								cout << "I don't understand you, guy!\n\n";
							}
						}else {
							if (strcmp(command, "open") == 0) {
								command = strtok(NULL, " ");
								if (command != NULL) {
									cout << player.Open(command) + "\n";

									i = 0;
									while ((player.room->objects.size() > i) && (strcmp(player.room->objects[i].getName(), command) != 0)) {
										++i;
									}
									for (int j = 0; j < player.room->objects[i].objects.size(); ++j) {
										cout << "- " + string(player.room->objects[i].objects[j].getName()) + "\n";
									}
								}
								else {
									cout << "I don't understand you, guy!\n\n";
								}
							}
							else {
								if (strcmp(command, "kill") == 0) {
									command = strtok(NULL, " ");
									if (command != NULL) {
										//busco el enemigo que quiere atacar
										j = 0;
										while (enemiesList.size() > j) {
											if ((strcmp(enemiesList[j].getName(), command) != 0) || (strcmp(player.room->getName(), enemiesList[j].room->getName()) != 0)) {
												++j;
											}
											else {
												break;
											}
										}
										if (j < enemiesList.size()){
											cout << player.Kill(enemiesList[j]);
											if (enemiesList[j].health < 1) {
												if (strcmp(enemiesList[j].getName(), "nobunaga")==0) {
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
								}
								else {
									if (strcmp(command, "throw") == 0) {
										command = strtok(NULL, " ");
										i = 0;
										//busco todas las palabras de la linea
										while (special[i] = strtok(NULL, " ")) {
											++i;
										}

										if ((command != NULL) && (i==2)) {
											//busco el enemigo que quiere atacar
											j = 0;
											while (enemiesList.size() > j) {
												if ((strcmp(enemiesList[j].getName(), special[1]) != 0) || (strcmp(player.room->getName(), enemiesList[j].room->getName()) != 0)) {
													++j;
												}
												else {
													break;
												}
											}
											if (j < enemiesList.size()) {
												cout << player.Throw(command, enemiesList[j]) + "\n";
												if (enemiesList[j].health < 1) {
													if (strcmp(enemiesList[j].getName(), "nobunaga")==0) {
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

		if (player.health < 1) {
			cout << "He killed you!\n\n";
			fin = true;
		}
	}
	while (_kbhit() == 0)
	{
		if (player.health < 1) {
			cout << "Ooooohhh you are dead.. \nNobunaga never died , got eternal life and ended up taking care of bonsai for all eternity. ";
		}
		else {
			cout << "You killed Nobunaga, your ninja clan became famous and people of Japan later achieved peace thanks to Tokugawa daimiyo. ";
		}
		while (_kbhit() == 0) {}
	}
	return 0;
}