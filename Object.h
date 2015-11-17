#pragma once
#include <string>
#include <vector>

using namespace std;

class Object
{
public:
	Object(char* obj, int num, char* text);
	Object(char* obj, int num, bool isOpen, vector<Object> objectsList);
	Object(char* obj, int num);
	Object();
	~Object();

	char* name;
	int quantity;
	bool readable;
	char* content;
	bool openable;
	bool open;
	vector<Object> objects;
};

