#include "World.h"

World::World()
{
}


World::~World()
{
}

void World::Init()
{
	//Initialize objects and list of objects for Scene
	Object *parchment = new Object("parchment", 1, "Your mission is kill the damiyo Nobunaga Oda. The damiyo is in Himeji castle for the next two nights.\nThe perfect moment to kill him is the night June 21, because the next day the damiyo recive a visit and there will be more guards.\nArchie\n\n");
	Object *carp = new Object("carp", 1);
	Object *kunai = new Object("kunai", 2);
	Object *shuriken = new Object("shuriken", 2);
	Object *katana = new Object("katana", 5);

	vector<Object> *objList = new vector<Object>();
	objList->push_back(*kunai);
	Object *box = new Object("box", 1, false, *objList);

	//Initialize the rooms
	objList->clear();
	objList->push_back(*box);

	Scene *pb1 = new Scene("PB1", "\nWest of Himeji castle\nYou are in the garden of Himeji castle. You can see some trees and walls to North and West.\n\n", *objList);
	Scene *pb2 = new Scene("PB2", "\nSouth-West of Himeji castle\nYou are in the garden of Himeji castle. You can see more trees and walls to South and East. Seems that nobody is guarding.\n\n");
	Scene *pb3 = new Scene("PB3", "\nSouth of Himeji castle\nYou can see a guard without armour in the stairs to the castle door (North). He can't see you because you are hiding behind a tree. To South you can see the wall door closed, to East you can hear somelike water flowing and to West you can see some trees.\n\n");
	objList->clear();
	objList->push_back(*carp);
	Scene *pb4 = new Scene("PB4", "\nSouth-East of Himeji castle\nYou can see a river with a red carp. To West you can see the entry of the castle, to North you can hear a little waterfall and East and South have walls.\n\n", *objList);
	Scene *pb5 = new Scene("PB5", "\nEast of Himeji castle\nYou can see a little waterfall with a little lake, tipical Japanese garden. To South the lake advance in a river form. North, East and West are walls. A centinel is warching the river.\n\n");
	objList->clear();
	objList->push_back(*box);
	Scene *pb6 = new Scene("PB6", "\nInside the castle\nYou can see four columns in the center of the hall. Seems that any guard are guarding the room. To East and West you can see stairs to the up floor. To South is the main entrance of the castle and in the north you can see a box.\n\n", *objList);
	Scene *p11 = new Scene("P11", "\nFirst floor hall\nYou can see four columns in the center of the hall. To East and West you can see stairs to the entrance of castle, to North you can see stairs to second floor and to South you can see a door.\n\n");
	objList->clear();
	objList->push_back(*katana);
	Scene *p12 = new Scene("P12", "\nFirst floor room\nYou can see a katana in the floor and a samurai backwards.\n\n", *objList);
	Scene *p21 = new Scene("P21", "\nSecond floor hall\nYou can see a samurai guarding a door to West.\n\n");
	Scene *p22 = new Scene("P22", "\nRoom of the damiyo Nobunaga\nNobunaga is facing away from you, looking at the stars through the balcony.\n\n");

	//Connecting the rooms
	Scene *ptrs = pb2;
	Scene *ptrn = NULL;
	Scene *ptre = NULL;
	Scene *ptrw = NULL;
	pb1->ConnectRooms(*ptrn, *ptre, *ptrs, *ptrw);

	ptrs = NULL;
	ptrn = pb1;
	ptre = pb3;
	ptrw = NULL;
	pb2->ConnectRooms(*ptrn, *ptre, *ptrs, *ptrw);

	ptrs = NULL;
	ptrn = pb6;
	ptre = pb4;
	ptrw = pb2;
	pb3->ConnectRooms(*ptrn, *ptre, *ptrs, *ptrw);

	ptrs = NULL;
	ptrn = pb5;
	ptre = NULL;
	ptrw = pb3;
	pb4->ConnectRooms(*pb5, *ptre, *ptrs, *ptrw);

	ptrs = pb4;
	ptrn = NULL;
	ptre = NULL;
	ptrw = NULL;
	pb5->ConnectRooms(*ptrn, *ptre, *ptrs, *ptrw);

	ptrs = pb3;
	ptrn = NULL;
	ptre = p11;
	ptrw = p11;
	pb6->ConnectRooms(*ptrn, *ptre, *ptrs, *ptrw);

	ptrs = p12;
	ptrn = p21;
	ptre = pb6;
	ptrw = pb6;
	p11->ConnectRooms(*ptrn, *ptre, *ptrs, *ptrw);

	ptrs = NULL;
	ptrn = p11;
	ptre = NULL;
	ptrw = NULL;
	p12->ConnectRooms(*ptrn, *ptre, *ptrs, *ptrw);

	ptrs = NULL;
	ptrn = p11;
	ptre = NULL;
	ptrw = p22;
	p21->ConnectRooms(*ptrn, *ptre, *ptrs, *ptrw);

	ptrs = NULL;
	ptrn = NULL;
	ptre = p21;
	ptrw = NULL;
	p22->ConnectRooms(*ptrn, *ptre, *ptrs, *ptrw);

	//Insert the rooms in vector
	scenes->push_back(*pb1);
	scenes->push_back(*pb2);
	scenes->push_back(*pb3);
	scenes->push_back(*pb4);
	scenes->push_back(*pb5);
	scenes->push_back(*pb6);
	scenes->push_back(*p11);
	scenes->push_back(*p12);
	scenes->push_back(*p21);
	scenes->push_back(*p22);

	//Initialize characters
	Scene *ptrChar = pb1;
	objList->clear();
	objList->push_back(*parchment);
	objList->push_back(*kunai);
	objList->push_back(*shuriken);
	objList->push_back(*shuriken);
	player = new Player(*ptrChar, *objList, 5);

	ptrChar = pb3;
	NPC guard = NPC("guard", 3, 1, false, *ptrChar);
	ptrChar = pb5;
	NPC guard2 = NPC("guard", 3, 1, true, *ptrChar);
	ptrChar = p12;
	NPC samurai = NPC("samurai", 5, 3, true, *ptrChar);
	ptrChar = p21;
	NPC samurai2 = NPC("samurai", 5, 3, true, *ptrChar);
	ptrChar = p22;
	NPC nobunaga = NPC("nobunaga", 5, 5, false, *ptrChar);

	enemiesList.push_back(guard);
	enemiesList.push_back(guard2);
	enemiesList.push_back(samurai);

	enemiesList.push_back(nobunaga);
}
