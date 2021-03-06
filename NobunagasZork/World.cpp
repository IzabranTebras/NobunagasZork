
#include "World.h"

World::World()
{
}


World::~World()
{
}

void World::Init()
{
	//Initialize the rooms
	Scene *pb1 = new Scene("PB1", "\nWest of Himeji castle\nYou are in the garden of Himeji castle. You can see some trees and walls to North and West.\n\n");
	Scene *pb2 = new Scene("PB2", "\nSouth-West of Himeji castle\nYou are in the garden of Himeji castle. You can see more trees and walls to South and East. Seems that nobody is guarding.\n\n");
	Scene *pb3 = new Scene("PB3", "\nSouth of Himeji castle\nYou can see two guards without armour on the stairs to the castle door (North). To South you can see the wall door closed, to East you can hear somelike water flowing and to West you can see some trees.\n\n");
	Scene *pb4 = new Scene("PB4", "\nSouth-East of Himeji castle\nYou can see a river and a carp in the water. To West you can see the entry of the castle, to North you can hear a little waterfall and East and South have walls.\n\n");
	Scene *pb5 = new Scene("PB5", "\nEast of Himeji castle\nYou can see a little waterfall with a little lake, tipical Japanese garden. To South the lake advance in a river form. North, East and West are walls. A sentinel is watching the river.\n\n");
	Scene *pb6 = new Scene("PB6", "\nInside the castle\nYou can see four columns in the center of the hall. Seems that any guard are guarding the hall. To East and West you can see stairs to the up floor. To South is the main entrance of the castle and in the north you can see a box in a shrine. In the shrine you can see a photo of a brown hair girl and a inscription that says: She will always be alive in our hearts.\n\n");
	Scene *p11 = new Scene("P11", "\nFirst floor hall\nYou can see four columns in the center of the hall. To East and West you can see stairs to the entrance of castle, to North you can see stairs to second floor and to South you hear screams through a door.\n\n");
	Scene *p12 = new Scene("P12", "\nFirst floor room\nYou can see a geisha on the floor and a samurai backwards. To North you can see a door to the hall.\n\n");
	Scene *p21 = new Scene("P21", "\nSecond floor hall\nYou can see downstairs to South and a samurai guarding a door to West.\n\n");
	Scene *p22 = new Scene("P22", "\nRoom of the damiyo Nobunaga\nNobunaga is facing away from you, looking at the stars through the balcony.\n\n");

	//Add alternative descriptions
	pb3->alternativeDescription = "\nSouth of Himeji castle\nYou can see two dead guards on the stairs. To South you can see the wall door closed, to East you can hear somelike water flowing and to West you can see some trees.\n\n";
	pb5->alternativeDescription = "\nEast of Himeji castle\nYou can see a little waterfall with a little lake, tipical Japanese garden. To South the lake advance in a river form. North, East and West are walls. A sentinel is sunk in the river.\n\n";
	p12->alternativeDescription = "\nFirst floor room\nYou can see a death samurai in the floor and a geisha beside him. To North you can see a door to the hall.\n\n";
	p21->alternativeDescription = "\nSecond floor hall\nYou can see a dead samurai in the floor next to a door to West and downstairs to South.\n\n";

	//Connecting the rooms
	pb1->ConnectRooms(NULL, NULL, pb2, NULL);
	pb2->ConnectRooms(pb1, pb3, NULL, NULL);
	pb3->ConnectRooms(pb6, pb4, NULL, pb2);
	pb4->ConnectRooms(pb5, NULL, NULL, pb3);
	pb5->ConnectRooms(NULL, NULL, pb4, NULL);
	pb6->ConnectRooms(NULL, p11, pb3, p11);
	p11->ConnectRooms(p21, pb6, p12, pb6);
	p12->ConnectRooms(p11, NULL, NULL, NULL);
	p21->ConnectRooms(p11, NULL, NULL, p22);
	p22->ConnectRooms(NULL, p21, NULL, NULL);

	//Insert the objects into the scenes
	vector<Object*> objList;
	objList.push_back(new Object("kunai", 2));
	pb6->objects.push_back(new Object("box", 1, false, objList));
	pb4->objects.push_back(new Object("carp", 9999));
	p12->objects.push_back(new Object("katana", 5));

	//Initialize objects
	objList.clear();
	objList.push_back(new Object("parchment", 1, "Your mission is kill the damiyo Nobunaga Oda. The damiyo is in Himeji castle for the next two nights.\nThe perfect moment to kill him is the night June 21, because the next day the damiyo recive a visit and there will be more guards.\nSigned, Archie\n\n"));
	objList.push_back(new Object("kunai", 2));
	objList.push_back(new Object("shuriken", 2));
	objList.push_back(new Object("shuriken", 2));
	objList.push_back(new Object("smoke", 0));
	objList.push_back(new Object("smoke", 0));
	player = new Player(pb1, objList, 5, 7, 2);

	//Initialize characters
	pb3->npcs.push_back(new NPC("guard", 3, 1, 3, false, "You bastard, come here!!\n"));
	pb3->npcs.push_back(new NPC("guard", 3, 1, 3, false, "You bastard, come here!!\n"));
	pb5->npcs.push_back(new NPC("sentinel", 2, 2, 3, true, "You bastard, come here!!\n"));
	p12->npcs.push_back(new NPC("samurai", 5, 3, 5, true, "You bastard, come here!!\n"));
	p12->npcs.push_back(new NPC("geisha", 1, 0, 1, false, "I'm Kaguya, take this katana and save us! Soon this world will change...\n\n"));
	p21->npcs.push_back(new NPC("samurai", 5, 3, 5, true, "You bastard, come here!!\n"));
	p22->npcs.push_back(new NPC("nobunaga", 5, 5, 7, false, "Who are you? How dare you interrupt my rest?!\nOh, i see... You come to kill me. Then get ready for combat, nameless ninja!!\n\n"));

	//Insert the rooms in vector
	scenes.push_back(pb1);
	scenes.push_back(pb2);
	scenes.push_back(pb3);
	scenes.push_back(pb4);
	scenes.push_back(pb5);
	scenes.push_back(pb6);
	scenes.push_back(p11);
	scenes.push_back(p12);
	scenes.push_back(p21);
	scenes.push_back(p22);
}