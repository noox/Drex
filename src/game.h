
#ifndef _GAME_H_
#define _GAME_H_

#include "world.h"
class game;
#include "menu.h"

class game{
	world w;
	menu m;
	int gamestatus,userchosen;
	int esc_hit;
public:
	void init();
	void finish();
	bool update(float timediff,bool space_down,bool tab_down,bool esc_down,bool left_mouse_down,bool right_mouse_down,int mouse_x,int mouse_y);
	void render();
	void change_userchosen(int userid);
	int get_userchosen();
	float get_min_timediff();
	void go_to_menu() {gamestatus=0;}
	void go_to_game() {gamestatus=1;}
};

#endif
