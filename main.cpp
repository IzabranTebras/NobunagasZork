#include <iostream>
#include <conio.h>
#include "Character.h"

using namespace std;

int main() {
	bool fin = false;
	char str[20];
	char* command;

	cout << "Nobunaga's Zork\n\n\n";

	//Initialize the rooms
	Scene pb1 = Scene("PB1", "Some trees...\n\n");
	Scene pb2 = Scene("PB2", "More trees...\n\n");
	Scene pb3 = Scene("PB3", "The stairs to the castle\n\n");
	Scene pb4 = Scene("PB4", "A river\n\n");
	Scene pb5 = Scene("PB5", "A waterfall\n\n");
	Scene pb6 = Scene("PB6", "Inside the castle\n\n");

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

	ptrs = NULL;
	ptrn = &pb1;
	ptre = &pb3;
	ptrw = NULL;
	pb6.ConnectRooms(*ptrn, *ptre, *ptrs, *ptrw);

	//Initialize the player
	Scene *ptrPlayer = &pb1;
	Character player = Character(*ptrPlayer);

	cout << player.room->description + "\n\n";

	while(!fin){
		if (_kbhit() != 0)
		{
			cin.getline(str, 20);
			command = strtok(str, " ");
			if (strcmp(command, "go") == 0) {
				command = strtok(NULL, " ");
				if (command != NULL) {
					cout << player.Go(command) + "\n\n";
				}
				else {
					cout << "I don't understand you, guy!\n\n";
				}
			}
		}
	}
	return 0;
}