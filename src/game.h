
#ifndef _GAME_H_
#define _GAME_H_

#include "dragon.h"
#include "heightmap.h"
#include "camera.h"
#include "menu.h"

class game{
	dragon dr;
	camera cam;
	heightmap hm;
	menu m;
	int texture;
	int gamestatus;
public:
	void init();
	void finish();
	bool update(float timediff,bool space_down,bool tab_down,bool esc_down,bool left_mouse_down,bool right_mouse_down,int mouse_x,int mouse_y);
	float get_min_timediff();
	void render();
};

#endif
