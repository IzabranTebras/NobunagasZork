#ifndef __Object__
#define __Object__

#include <vector>

using namespace std;

class Object
{
public:
	Object(const char* obj, const int damage, const char* text);
	Object(const char* obj, const int damage, const bool isOpen, const vector<Object*> objectsList);
	Object(const char* obj, const int damage);
	Object();
	~Object();

	const char* getName() const;
	const char* getLecture() const;
	const bool getReadable() const;
	const bool getOpenable() const;
	const int getDamageAttack() const;
	const bool getOpen() const;
	const void setOpen(bool nowOpen);

	vector<Object*> objects;

private:
	const char* name;
	bool readable;
	const char* lecture;
	bool openable;
	int damageAttack;
	bool open;
};

#endif