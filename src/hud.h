
#ifndef _HUD_H_
#define _HUD_H_

#include "../vendor/OGLFT.h"

class world;

class hud
{
	int counter;
	OGLFT::TranslucentTexture *white_font;
	void beginning();
	void ending();
public:
	void init();
	void make_healthstatus(float dargon_hp);
	void make_dragon_hit();
	void draw_tutorial();
};

#endif

