
#include "game.h"

#ifndef _CREATION_H_
#define _CREATION_H_

#include <vector>
#include <string>

using namespace std;

#include "vector.h"

#include "../vendor/OGLFT.h"

enum type {
	water,
	lowland,
	upland,
	mountain,
	estate,
	no_estate
};

class types
{
public:
	float r, g, b;
	bool active;
	string name, color;
};

class creation
{
	OGLFT::TranslucentTexture *face, *face2;
	int left_mouse_hit, esc_hit, status, type;
	bool go_next;
	vector<int> terrain, final_terrain, terrain_to_save, units;
	int weather, daytime, difficulty, active_weather, active_daytime, 
		active_difficulty;
public:
	int i, j, x, y, z, zz, scale, cursor_pos_x, cursor_pos_y;
	vector<types> data;
	void init();
	void finish();
	void set();
	void prepare_map();
	void blur();
	void save_map(game& g);
	int get_type();
	void get_settings();
	bool someone_on_map();
	bool terrain_on_map();
	bool update(float timediff, bool space_down, bool esc_down, 
		bool left_mouse_down, bool right_mouse_down, int mouse__x, 
		int mouse__y, game& g);
	void make_quad(int empty);
	void render();
};

#endif

