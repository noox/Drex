
#include "game.h"

#ifndef _MENU_H_
#define _MENU_H_

#include <vector>
#include <string>

using namespace std;

#include "../vendor/OGLFT.h"

class menu
{
	OGLFT::TranslucentTexture *title_font, *username_font, *blue_font,
		*blue_alpha_font, *white_font;
	int menustatus;
	int cursor_pos;
	int left_mouse_hit, esc_hit;
	int sens_id, dayt_id, weat_id, diff_id, camp_id;
	int maps_in_campaign;
	bool new_one, new_one_plays, active;
	string mapname, username, name, sens, dayt, weat, diff, camp;
	vector<pair<string, int> > items;
	vector<string> daytime, weather, difficulty, sensitivities, campaign;
public:
	void init();
	void finish();
	bool update(float timediff, bool esc_down, bool left_mouse_down, 
		bool right_mouse_down, int mouse_x, int mouse_y, game& g);
	void go_to_winscreen(game& g);
	void go_to_failscreen();
	void go_to_menu_or_back();
	void render();
	bool handle_menu_click(int item, game& g, int esc_just_pressed);
	void set_menu(int newstatus);
};

#endif

