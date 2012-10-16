
#ifndef _MENU_H_
#define _MENU_H_

#include "../vendor/OGLFT.h"

class menu {
public:
	OGLFT::TranslucentTexture *face, *face2, *face3;
	int cursor_pos;
	int menustatus;

	void init();
	bool update(float timediff,bool esc_down,bool left_mouse_down,bool right_mouse_down,int mouse_x,int mouse_y);
	void render();
};

#endif

