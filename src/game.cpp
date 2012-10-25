
#include <iostream>

using namespace std;

#include "game.h"

#include "imageloader.h"
#include "world.h"
#include "menu.h"

//status hry: 0 menu, 1 hra, 2 vitezstvi, 3 prohra

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
	
	switch (gamestatus){
		case 0:
			if(!m.update(timediff,esc_down,left_mouse_down,right_mouse_down,mouse_x,mouse_y,*this)) return false;
			if(esc_just_pressed) return false;
			else return true;;
			return true;
			break;
		case 1:
			w.update(timediff,space_down,tab_down,esc_down,left_mouse_down,right_mouse_down,mouse_x,mouse_y);
			if(esc_just_pressed) go_to_menu();
			else return true;
			break;
		case 2:
			break;
		case 3:
			break;
	}
}

float game::get_min_timediff(){
	return 0.02;
}

void game::render(){
	switch (gamestatus){
		case 0: 
			m.render();
			break;
		case 1: 
			w.render();
			break;
		case 2:
			break;
		case 3:
			break;
	}
}

