
#ifndef _GAME_H_
#define _GAME_H_

class game{
public:
	void init();
	void finish();
	bool update(float timediff,bool space_down,bool tab_down,bool esc_down,bool left_mouse_down,bool right_mouse_down,int mouse_x,int mouse_y);
	float get_min_timediff();
	void render();
};

#endif
