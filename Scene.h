#include <string>

using namespace std;

class Scene
{
public:
	Scene(const string name, const string text);
	Scene();
	~Scene();
	void ConnectRooms(Scene &north, Scene &east, Scene &south, Scene &west);

	string description;
	string name;
	Scene *north;
	Scene *east;
	Scene *south;
	Scene *west;
};

