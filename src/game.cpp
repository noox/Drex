
#include <iostream>

using namespace std;

#include "game.h"

#include "world.h"
#include "menu.h"

//status hry: 0 menu, 1 hra

void game::init(){
	w.init();
	m.init();
	gamestatus=0;
	esc_hit=0;
}

void game::finish(){
	w.finish();
}

bool game::update(float timediff,bool space_down,bool tab_down,bool esc_down,bool left_mouse_down,bool right_mouse_down,int mouse_x,int mouse_y){
	int esc_just_pressed=0;
	//proti sekvencim stisknutych tlacitek
	if (esc_down) {
		if (!esc_hit)
			esc_just_pressed=esc_hit=1;
	} else esc_hit=0;

	
	if(gamestatus==0) {
		//v menu
		if(!m.update(timediff,esc_down,left_mouse_down,right_mouse_down,mouse_x,mouse_y,*this)) return false;
		return true;
	} else {
		//ve hre
		if(!w.update(timediff,space_down,tab_down,esc_down,left_mouse_down,right_mouse_down,mouse_x,mouse_y)) {
			go_to_menu();
			m.go_to_winscreen();
		}
		else if(esc_just_pressed) go_to_menu();
		return true;
	}
}

float game::get_min_timediff(){
	return 0.02;
}

void game::render(){
	if(gamestatus==0) m.render();
	else w.render();
}

