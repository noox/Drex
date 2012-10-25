

#ifndef _WORLD_H_
#define _WORLD_H_

#include "dragon.h"
#include "heightmap.h"
#include "camera.h"

class world{
	dragon dr;
	camera cam;
	heightmap hm;
	int texture;
public:
	void init();
	void finish();
	bool update(float timediff,bool space_down,bool tab_down,bool esc_down,bool left_mouse_down,bool right_mouse_down,int mouse_x,int mouse_y);
	void render();
};

#endif
