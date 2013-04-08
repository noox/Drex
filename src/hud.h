
#ifndef _HUD_H_
#define _HUD_H_

#include "../vendor/OGLFT.h"

class world;

class hud
{
	OGLFT::TranslucentTexture *white_font;
	void begining();
	void ending();
public:
	void init();
	void make_healthstatus(float dargon_hp);
	void make_dragon_hit();
	void draw_tutorial(world& w);
};

#endif

