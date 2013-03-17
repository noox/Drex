
#include "game.h"

#ifndef _CREATION_H_
#define _CREATION_H_

#include <vector>
#include <string>

using namespace std;

#include "vector.h"

#include "../vendor/OGLFT.h"

enum type {
	mountain,
	upland,
	lowland,
	water,
	house
};

class types {
public:
	float r, g, b;
	bool active;
	string name;
};

class creation {
	OGLFT::TranslucentTexture *face, *face2;
	int left_mouse_hit, esc_hit, status, type;
	vector<int> terrain, units;
public:
	int x, y, cursor_pos_x, cursor_pos_y;
	vector<types> data;
	void init();
	void set();
	int get_type();
	bool update (float timediff, bool space_down, bool esc_down, bool left_mouse_down, bool right_mouse_down, int mouse__x, int mouse__y, game& g);
	void render();
};

#endif

