#ifndef __Object__
#define __Object__

#include <string>
#include <vector>

using namespace std;

class Object
{
public:
	Object(char* obj, int damage, char* text);
	Object(char* obj, int damage, bool isOpen, vector<Object> objectsList);
	Object(char* obj, int damage);
	Object();
	~Object();

	const char* getName();
	const char* getContent();
	const bool getReadable();
	const bool getOpenable();
	const int getDamageAttack();
	const bool getOpen();
	const void setOpen(bool nowOpen);

	vector<Object> objects;

private:
	const char* name;
	bool readable;
	const char* content;
	bool openable;
	int damageAttack;
	bool open;
};

#endif