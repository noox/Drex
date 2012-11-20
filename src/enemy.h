
#include <list>

using namespace std;

#include "vector.h"

class enemy {
public:
	vect pos, spd;
	int type;
	float hp;
	bool burning;

	enemy() {}

	void create();
	void update(float time);
	void draw();
	bool deletable();
};

class enemy_system {
public:
	list<enemy> enemies;

	void init();
	enemy& add_one();
	void update(float time);
	void draw();
	void finish();
};

