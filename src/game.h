
#ifndef _GAME_H_
#define _GAME_H_

#include "world.h"
class game;
#include "menu.h"

class game{
	world w;
	menu m;
	//0 menu, 1 hra
	int gamestatus;
	//0 day, 1 night
	int daytime;
	//0 sunny, 1 rainy, 2 snowy
	int weather;
	//0 easy, 1 medium, 2 hard
	int difficulty;
	int esc_hit;
	int mapchosen,userchosen;
	float sensitivity;
public:
	void init();
	void finish();
	bool update(float timediff,bool space_down,bool tab_down,bool esc_down,bool left_mouse_down,bool right_mouse_down,int mouse_x,int mouse_y);
	void render();
	void change_userchosen(int Userchosen);
	int get_userchosen();
	void change_mapchosen(int Mapchosen);
	int get_mapchosen();
	void change_sensitivity(float Sensitivity);
	float get_sensitivity();
	void change_daytime(int Daytime);
	int get_daytime();
	void change_weather(int Weather);
	int get_weather();
	void change_difficulty(int Difficulty);
	int get_difficulty();
	float get_min_timediff();
	void go_to_menu() {gamestatus=0;}
	void go_to_game() {gamestatus=1;}
};

#endif
