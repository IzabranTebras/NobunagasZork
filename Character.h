#include <string>
#include "Scene.h"

class Character
{
public:
	Character(Scene &loc);
	Character();
	~Character();

	string Go(char* direction);

	Scene *room;

};

