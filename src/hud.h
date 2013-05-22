
#ifndef _HUD_H_
#define _HUD_H_

#include "../vendor/OGLFT.h"

class world;

class hud
{
	int counter;
	int width, height;
	OGLFT::TranslucentTexture *white_font;
	void beginning();
	void ending();
public:
	void init(world& w);
	void make_healthstatus(float dragon_hp);
	void make_dragon_hit();
	void draw_cheat();
	void draw_tutorial();
};

#endif

