
#include "game.h"

#ifndef _WORLD_H_
#define _WORLD_H_

#include "dragon.h"
#include "heightmap.h"
#include "camera.h"
#include "skybox.h"
#include "fog.h"
#include "enemy.h"
#include "objects.h"
#include "particles.h"
#include "missiles.h"

class world {
public:
	dragon dr;
	camera cam;
	heightmap hm;
	skybox skyb;
	fog f;
	enemy_system es;
	object_system ob;
	particle_system ps;
	missile_system ms;

	int tab_hit;
	bool help_on;
	int weather;
	int daytime;

	int texture;
	void init();
	void finish();
	int update (float timediff, bool space_down, bool tab_down, bool esc_down, bool left_mouse_down, bool right_mouse_down, int mouse_x, int mouse_y, game &g);
	void render();
};

#endif
