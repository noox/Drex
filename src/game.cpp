
#include <GL/gl.h>

#include "game.h"

void game::init(){
}

void game::finish(){
}

bool game::update(float timediff,bool space_down,bool tab_down,bool esc_down,bool left_mouse_down,bool right_mouse_down,int mouse_x,int mouse_y){
	if(esc_down) return false;
	else return true;
}

float game::get_min_timediff(){
	return 0.02;
}

void game::render(){
	glClearColor(0,0,1,0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}
