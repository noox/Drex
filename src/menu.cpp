
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

#include "menu.h"
#include "maplist.h"
#include "userlist.h"

#include "../vendor/OGLFT.h"

void menu::init() {
	face = new OGLFT::TranslucentTexture ("data/DK Northumbria.otf", 150);
	face2 = new OGLFT::TranslucentTexture ("data/DK Northumbria.otf", 50);
	face3 = new OGLFT::TranslucentTexture ("data/DK Northumbria.otf", 30);
	if (face == 0 || face2 == 0 || face3 == 0 || !face->isValid() || !face2->isValid() || !face3->isValid() ) {
		cerr << "Could not construct face." << endl;
		return;
	}
	name_file_init();
	left_mouse_hit = 0;
	esc_hit = 0;
	cursor_pos = 0;
	set_menu (0);
	name = "";

	sensitivities.push_back ("0.01");
	sensitivities.push_back ("0.05");
	sensitivities.push_back ("0.1");
	sensitivities.push_back ("0.5");
	sensitivities.push_back ("1");
	sensitivities.push_back ("5");
	sensitivities.push_back ("10");
	sensitivities.push_back ("50");
	sensitivities.push_back ("100");
	sensitivities.push_back ("500");
	sens_id = 4;
	sens = sensitivities[sens_id];

	daytime.push_back ("day");
	daytime.push_back ("night");
	dayt_id = day;
	dayt = daytime[dayt_id];

	weather.push_back ("sunny");
	weather.push_back ("rainy");
	weather.push_back ("snowy");
	weat_id = sunny;
	weat = weather[weat_id];

	difficulty.push_back ("easy");
	difficulty.push_back ("medium");
	difficulty.push_back ("hard");
	diff_id = easy;
	diff = difficulty[diff_id];
}

void menu::set_menu (int newstatus) {
	menustatus = newstatus;
	items.clear();
	switch (newstatus) {
		//hlavni menu
	case 0:
		items.push_back (make_pair("campaign", 0));
		items.push_back (make_pair("missions", 0));
		items.push_back (make_pair("options", 0));
		items.push_back (make_pair("exit", 0));
		break;
		//kampan
	case 1:
		items.push_back (make_pair("tutorial", 0));
		items.push_back (make_pair("mission 1", 0));
		items.push_back (make_pair("mission 2", 0));
		items.push_back (make_pair("back", 0));
		break;
		//jednotlive mise
	case 2:
		items.push_back (make_pair("choose map", 0));
		items.push_back (make_pair("daytime", 0));
		items.push_back (make_pair("weather", 0));
		items.push_back (make_pair("difficulty", 0));
		items.push_back (make_pair("play", 0));
		items.push_back (make_pair("back", 0));
		break;
		//nastaveni
	case 3:
		items.push_back (make_pair("player", 0));
		items.push_back (make_pair("mouse sensitivity", 0));
		items.push_back (make_pair("back", 0));
		break;
		//vyber mapy
	case 4:
		items.push_back (make_pair("previous", 1));
		items.push_back (make_pair(mapname, 0));
		items.push_back (make_pair("next", 1));
		break;
		//denni doba
	case 5:
		items.push_back (make_pair("previous", 1));
		items.push_back (make_pair(dayt, 0));
		items.push_back (make_pair("next", 1));
		break;
		//pocasi
	case 6:
		items.push_back (make_pair("previous", 1));
		items.push_back (make_pair(weat, 0));
		items.push_back (make_pair("next", 1));
		break;
		//obtiznost hry
	case 7:
		items.push_back (make_pair("previous", 1));
		items.push_back (make_pair(diff, 0));
		items.push_back (make_pair("next", 1));
		break;
		//hrac
	case 8:
		items.push_back (make_pair("new player", 0));
		items.push_back (make_pair("choose account", 0));
		items.push_back (make_pair("back", 0));
		break;
		//nastaveni mysi
	case 9:
		items.push_back (make_pair("higher", 1));
		items.push_back (make_pair(sens, 0));
		items.push_back (make_pair("lower", 1));
		break;
		//novy hrac
	case 10:
		items.push_back (make_pair("get name", 0));
		items.push_back (make_pair(name, 0));
		items.push_back (make_pair("ok", 0));
		break;
		//vyber accountu
	case 11:
		items.push_back (make_pair("previous", 1));
		items.push_back (make_pair(username, 0));
		items.push_back (make_pair("next", 1));
		break;
		//vitezny screen
	case 12:
		items.push_back (make_pair("victory", 0));
		break;
		//prohrany screen
	case 13:
		items.push_back (make_pair("failure", 0));
		break;
	}
	if ( (newstatus != 4) && (newstatus != 5) && (newstatus != 6) && (newstatus != 7) && (newstatus != 9) && (newstatus != 11) ) cursor_pos = 0;
}

bool menu::handle_menu_click (int item, game& g, int esc_just_pressed) {
	ostringstream ss;
	int mapchosen = g.get_mapchosen();
	int userchosen = g.get_userchosen();
	if (esc_just_pressed) item = -1;
	switch (menustatus) {
		//hlavni menu
	case 0:
		switch (item) {
		case 0:
			set_menu (1);
			break;
		case 1:
			set_menu (2);
			break;
		case 2:
			set_menu (3);
			break;
		case 3:
			return false;
		case -1:
			return false;
		}
		break;
		//kampan
	case 1:
		switch (item) {
		case 0:
			g.go_to_game();
			break;
		case 1:
			g.go_to_game();
			break;
		case 2:
			g.go_to_game();
			break;
		case 3:
			set_menu (0);
			break;
		case -1:
			set_menu (0);
			break;
		}
		break;
		//jednotlive mise
	case 2:
		switch (item) {
		case 0:
			set_menu (4);
			break;
		case 1:
			set_menu (5);
			break;
		case 2:
			set_menu (6);
			break;
		case 3:
			set_menu (7);
			break;
		case 4:
			g.go_to_game();
			break;
		case 5:
			set_menu (0);
			break;
		case -1:
			set_menu (0);
			break;
		}
		break;
		//nastaveni
	case 3:
		switch (item) {
		case 0:
			set_menu (8);
			break;
		case 1:
			set_menu (9);
			break;
		case 2:
			set_menu (0);
			break;
		case -1:
			set_menu (0);
			break;
		}
		break;
		//vyber mapy
	case 4:
		switch (item) {
		case 0:
			//posuvnik nahoru
			mapchosen--;
			if (mapchosen < 0) mapchosen = 0;
			g.change_mapchosen (mapchosen);
			mapname = maplist_get_name (mapchosen);
			set_menu (4);
			break;
		case 1:
			//nazev mapy k vyberu
			g.change_mapchosen (mapchosen);
			mapname = maplist_get_name (mapchosen);
			set_menu (2);
			break;
		case 2:
			//posuvnik dolu
			mapchosen++;
			if (mapchosen > maplist_count() - 1) mapchosen = maplist_count() - 1;
			g.change_mapchosen (mapchosen);
			mapname = maplist_get_name (mapchosen);
			set_menu (4);
			break;
		case -1:
			set_menu (2);
			break;
		}
		break;
		//denni doba
	case 5:
		switch (item) {
		case 0:
			//posuvnik nahoru
			dayt_id--;
			if (dayt_id < 0) dayt_id = 0;
			g.change_daytime (dayt_id);
			dayt = daytime[dayt_id];
			set_menu (5);
			break;
		case 1:
			//konkretni denni doba k vyberu
			g.change_daytime (dayt_id);
			dayt = daytime[dayt_id];
			set_menu (2);
			break;
		case 2:
			//posuvnik dolu
			dayt_id++;
			if (dayt_id > daytime.size() - 1) dayt_id = daytime.size() - 1;
			g.change_daytime (dayt_id);
			dayt = daytime[dayt_id];
			set_menu (5);
			break;
		case -1:
			set_menu (2);
			break;
		}
		break;
		//pocasi
	case 6:
		switch (item) {
		case 0:
			//posuvnik nahoru
			weat_id--;
			if (weat_id < 0) weat_id = 0;
			g.change_weather (weat_id);
			weat = weather[weat_id];
			set_menu (6);
			break;
		case 1:
			//konkretni pocasi k vyberu
			g.change_weather (weat_id);
			weat = weather[weat_id];
			set_menu (2);
			break;
		case 2:
			//posuvnik dolu
			weat_id++;
			if (weat_id > weather.size() - 1) weat_id = weather.size() - 1;
			g.change_weather (weat_id);
			weat = weather[weat_id];
			set_menu (6);
			break;
		case -1:
			set_menu (2);
			break;
		}
		break;
		//obtiznost hry
	case 7:
		switch (item) {
		case 0:
			//posuvnik nahoru
			diff_id--;
			if (diff_id < 0) diff_id = 0;
			g.change_difficulty (diff_id);
			diff = difficulty[diff_id];
			set_menu (7);
			break;
		case 1:
			//konkretni obtiznost k vyberu
			g.change_difficulty (diff_id);
			diff = difficulty[diff_id];
			set_menu (2);
			break;
		case 2:
			//posuvnik dolu
			diff_id++;
			if (diff_id > difficulty.size() - 1) diff_id = difficulty.size() - 1;
			g.change_difficulty (diff_id);
			diff = difficulty[diff_id];
			set_menu (7);
			break;
		case -1:
			set_menu (2);
			break;
		}
		break;
		//hrac
	case 8:
		switch (item) {
		case 0:
			//pred spustenim randomizeru jmen - prazdno
			name = "";
			set_menu (10);
			break;
		case 1:
			set_menu (11);
			break;
		case 2:
			set_menu (3);
			break;
		case -1:
			set_menu (3);
			break;
		}
		break;
		//nastaveni mysi
	case 9:
		switch (item) {
		case 0:
			//posuvnik nahoru
			sens_id--;
			if (sens_id < 0) sens_id = 0;
			g.change_sensitivity (sens_id);
			sens = sensitivities[sens_id];
			set_menu (9);
			break;
		case 1:
			//sensitivita mysi k vyberu
			g.change_sensitivity (sens_id);
			sens = sensitivities[sens_id];
			set_menu (3);
			break;
		case 2:
			//posuvnik dolu
			sens_id++;
			if (sens_id > sensitivities.size() - 1) sens_id = sensitivities.size() - 1;
			g.change_sensitivity (sens_id);
			sens = sensitivities[sens_id];
			set_menu (9);
			break;
		case -1:
			set_menu (3);
			break;
		}
		break;
		//novy hrac
	case 10:
		switch (item) {
		case 0:
			//vygeneruje jmeno pro noveho hrace
			name = get_random_name (1);
			set_menu (10);
			break;
		case 2:
			//kontrola pro nevygenerovane jmeno
			if (name == "") {
				set_menu (10);
				break;
			}
			//pri zvoleni jmena, zaridi vse potrebne
			g.change_userchosen (make_user (name) );
			username = name;
			set_menu (8);
			break;
		case -1:
			set_menu (8);
			break;
		}
		break;
		//vyber accountu
	case 11:
		switch (item) {
		case 0:
			//posuvnik nahoru
			userchosen--;
			if (userchosen < 0) userchosen = 0;
			g.change_userchosen (userchosen);
			username = userlist_get_name (userchosen);
			set_menu (11);
			break;
		case 1:
			//jmeno uctu k vyberu
			g.change_userchosen (userchosen);
			username = userlist_get_name (userchosen);
			if (username == "") set_menu (11);
			else set_menu (8);
			break;
		case 2:
			//posuvnik dolu
			userchosen++;
			if (userchosen > userlist_count() - 1) userchosen = userlist_count() - 1;
			g.change_userchosen (userchosen);
			username = userlist_get_name (userchosen);
			set_menu (11);
			break;
		case -1:
			set_menu (8);
			break;
		}
		break;
		//vitezny screen
	case 12:
		set_menu (0);
		if (item == -1) set_menu (0);
		break;
		//prohrany screen
	case 13:
		set_menu (0);
		if (item == -1) set_menu (0);
		break;
	}
	return true;
}

void menu::go_to_winscreen() {
	set_menu (12);
}

void menu::go_to_failscreen() {
	set_menu (13);
}


bool menu::update (float timediff, bool esc_down, bool left_mouse_down, bool right_mouse_down, int mouse_x, int mouse_y, game& g) {
	//aktualni hodnoty pro prichod do podmenu
	mapname = maplist_get_name (g.get_mapchosen() );
	username = userlist_get_name (g.get_userchosen() );
	sens = sensitivities[g.get_sensitivity() ];
	dayt = daytime[g.get_daytime() ];
	weat = weather[g.get_weather() ];
	diff = difficulty[g.get_difficulty() ];
	//urceni pozice kurzoru
	cursor_pos += mouse_y;
	if (cursor_pos >= (int) (items.size() *100) ) cursor_pos = (int) (items.size() * 100 - 1);
	if (cursor_pos < 0) cursor_pos = 0;

	int left_just_pressed = 0, esc_just_pressed = 0;
	//proti sekvencim stisknutych tlacitek
	if (left_mouse_down) {
		if (!left_mouse_hit)
			left_just_pressed = left_mouse_hit = 1;
	} else left_mouse_hit = 0;
	if (esc_down) {
		if (!esc_hit)
			esc_just_pressed = esc_hit = 1;
	} else esc_hit = 0;

	//vyber submenu
	if (left_just_pressed || esc_just_pressed)
		if (!handle_menu_click (cursor_pos / 100, g, esc_just_pressed) )
			return false;

	return true;
}

void menu::render() {
	glDisable (GL_DEPTH_TEST);
	glClearColor (0, 0, 0, 0);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glOrtho (0, 800, 0, 600, 1, -1);
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();

	face->setBackgroundColor (1, 0, 0, 0);
	face2->setBackgroundColor (0, 0.75, 0.75, 0);
	face3->setBackgroundColor (0, 1, 0.5, 0);
	face->setForegroundColor (1, 0, 0, 1);
	face2->setForegroundColor (0, 0.75, 0.75, 1);
	face3->setForegroundColor (0, 1, 0.5, 1);
	face2->setHorizontalJustification (OGLFT::Face::CENTER);
	face3->setHorizontalJustification (OGLFT::Face::CENTER);
	glPixelStorei (GL_UNPACK_ALIGNMENT, 1);
	glColor3f (1, 0, 1);
	glEnable (GL_TEXTURE_2D);
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	if(username!="") {
		glPushMatrix();
		glTranslatef (250, 545, 0);
		glScalef (0.15, 0.15, 1);
		face->setHorizontalJustification (OGLFT::Face::LEFT);
		face->setForegroundColor (1, 0, 0, 0.95);
		face->draw (0, 0, (username + "'s").c_str() );
		face->setForegroundColor (1, 0, 0, 1);
		glPopMatrix();
	}

	glPushMatrix();
	glTranslatef (400, 415, 0);
	face->setHorizontalJustification (OGLFT::Face::CENTER);
	face->draw (0, 0, "drex");
	glPopMatrix();

	glPushMatrix();
	glTranslatef (400, 325, 0);
	for (int i = 0;i < items.size();++i) {
		string t = items[i].first;
		if (cursor_pos / 100 == i)
			t = "+ " + t + " +";
		if (items[i].second == 1) {
			face2->setBackgroundColor (0, 0.75, 0.75, 0);
			face2->setForegroundColor (0, 0.75, 0.75, 0.75);
		}
		face2->draw (0, 0, t.c_str() );
		face2->setBackgroundColor (0, 0.75, 0.75, 0);
		face2->setForegroundColor (0, 0.75, 0.75, 1);
		glTranslatef (0, -60, 0);
	}
	glPopMatrix();

	glDisable (GL_BLEND);
	glDisable (GL_TEXTURE_2D);

	glEnable (GL_DEPTH_TEST);
}

