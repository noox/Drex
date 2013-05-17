
#include <iostream>
#include <sstream>

using namespace std;

#include "menu.h"
#include "maplist.h"
#include "userlist.h"

void menu::init()
{
	title_font = 
		new OGLFT::TranslucentTexture("data/DK Northumbria.otf", 150);
	username_font = 
		new OGLFT::TranslucentTexture("data/DK Northumbria.otf", 21);
	blue_font = 
		new OGLFT::TranslucentTexture("data/DK Northumbria.otf", 50);
	blue_alpha_font = 
		new OGLFT::TranslucentTexture("data/DK Northumbria.otf", 50);
	white_font = 
		new OGLFT::TranslucentTexture("data/DK Northumbria.otf", 10);
	
	if (title_font == 0 || username_font == 0 || blue_font == 0 || 
		blue_alpha_font == 0 || white_font == 0 ||
		!title_font->isValid() || !username_font->isValid() || 
		!blue_font->isValid() || !blue_alpha_font->isValid() ||
		!white_font->isValid()) {

		cerr << "Could not construct face." << endl;
		return;
	}

	title_font->setForegroundColor(1, 0, 0, 1);
	title_font->setBackgroundColor(1, 0, 0, 0);
	title_font->setHorizontalJustification(OGLFT::Face::CENTER);
	username_font->setForegroundColor(1, 0, 0, 0.95);
	username_font->setBackgroundColor(1, 0, 0, 0);
	username_font->setHorizontalJustification(OGLFT::Face::LEFT);
	blue_font->setForegroundColor(0, 0.75, 0.75, 1);
	blue_font->setBackgroundColor(0, 0.75, 0.75, 0);
	blue_font->setHorizontalJustification(OGLFT::Face::CENTER);
	blue_alpha_font->setForegroundColor(0, 0.75, 0.75, 0.75);
	blue_alpha_font->setBackgroundColor(0, 0.75, 0.75, 0);
	blue_alpha_font->setHorizontalJustification(OGLFT::Face::CENTER);
	white_font->setBackgroundColor(1, 1, 1, 0);
	white_font->setForegroundColor(1, 1, 1, 1);
	white_font->setHorizontalJustification(OGLFT::Face::LEFT);

	name_file_init();
	left_mouse_hit = 0;
	esc_hit = 0;
	cursor_pos = 0;
	set_menu(0);
	name = "";
	new_one = false;
	new_one_plays = false;
	active = true;

	sensitivities.push_back("0.01");
	sensitivities.push_back("0.05");
	sensitivities.push_back("0.1");
	sensitivities.push_back("0.5");
	sensitivities.push_back("1");
	sensitivities.push_back("5");
	sensitivities.push_back("10");
	sensitivities.push_back("50");
	sensitivities.push_back("100");
	sensitivities.push_back("500");
	sens_id = 4;
	sens = sensitivities[sens_id];

	daytime.push_back("day");
	daytime.push_back("night");
	dayt_id = day;
	dayt = daytime[dayt_id];

	weather.push_back("sunny");
	weather.push_back("rainy");
	weather.push_back("snowy");
	weat_id = sunny;
	weat = weather[weat_id];

	difficulty.push_back("easy");
	difficulty.push_back("medium");
	difficulty.push_back("hard");
	diff_id = easy;
	diff = difficulty[diff_id];

	maps_in_campaign = 0;

	campaign.push_back("tutorial");
	for (int i = 1;i <= maps_in_campaign;++i) { 
		ostringstream ss;
		ss << i;
		string tmp = "mission" + ss.str();
		campaign.push_back(tmp);
	}
	camp_id = 0;
	camp = campaign[camp_id];
}

void menu::finish()
{
	items.clear();
	sensitivities.clear();
	daytime.clear();
	weather.clear();
	difficulty.clear();
	campaign.clear();
}

void menu::set_menu(int newstatus)
{
	menustatus = newstatus;
	items.clear();
	switch (newstatus) {
		//hlavni menu
	case 0:
		items.push_back(make_pair("campaign", 0));
		items.push_back(make_pair("missions", 0));
		items.push_back(make_pair("options", 0));
		items.push_back(make_pair("map creation", 0));
		items.push_back(make_pair("exit", 0));
		break;
		//kampan
	case 1:
		items.push_back(make_pair("previous", 1));
		if (active) items.push_back(make_pair(camp, 0));
		else items.push_back(make_pair(camp, 1));
		items.push_back(make_pair("next", 1));
		break;
		//jednotlive mise
	case 2:
		items.push_back(make_pair("choose map", 0));
		items.push_back(make_pair("daytime", 0));
		items.push_back(make_pair("weather", 0));
		items.push_back(make_pair("difficulty", 0));
		items.push_back(make_pair("play", 0));
		items.push_back(make_pair("back", 0));
		break;
		//nastaveni
	case 3:
		items.push_back(make_pair("player", 0));
		items.push_back(make_pair("mouse sensitivity", 0));
		items.push_back(make_pair("back", 0));
		break;
		//vyber mapy
	case 4:
		items.push_back(make_pair("previous", 1));
		items.push_back(make_pair(mapname, 0));
		items.push_back(make_pair("next", 1));
		break;
		//denni doba
	case 5:
		items.push_back(make_pair("previous", 1));
		items.push_back(make_pair(dayt, 0));
		items.push_back(make_pair("next", 1));
		break;
		//pocasi
	case 6:
		items.push_back(make_pair("previous", 1));
		items.push_back(make_pair(weat, 0));
		items.push_back(make_pair("next", 1));
		break;
		//obtiznost hry
	case 7:
		items.push_back(make_pair("previous", 1));
		items.push_back(make_pair(diff, 0));
		items.push_back(make_pair("next", 1));
		break;
		//hrac
	case 8:
		items.push_back(make_pair("new player", 0));
		items.push_back(make_pair("choose account", 0));
		items.push_back(make_pair("back", 0));
		break;
		//nastaveni mysi
	case 9:
		items.push_back(make_pair("higher", 1));
		items.push_back(make_pair(sens, 0));
		items.push_back(make_pair("lower", 1));
		break;
		//novy hrac
	case 10:
		items.push_back(make_pair("get name", 0));
		items.push_back(make_pair(name, 0));
		items.push_back(make_pair("ok", 0));
		break;
		//vyber accountu
	case 11:
		items.push_back(make_pair("previous", 1));
		items.push_back(make_pair(username, 0));
		items.push_back(make_pair("next", 1));
		break;
		//vitezny screen
	case 12:
		items.push_back(make_pair("victory", 0));
		break;
		//prohrany screen
	case 13:
		items.push_back(make_pair("failure", 0));
		break;
	}

	if ((newstatus != 1) && (newstatus != 4) && (newstatus != 5) && 
		(newstatus != 6) && (newstatus != 7) && (newstatus != 9) &&
		(newstatus != 11)) cursor_pos = 0;
}

bool menu::handle_menu_click(int item, game& g, int esc_just_pressed)
{
	ostringstream ss;
	int mapchosen = g.get_mapchosen();
	int userchosen = g.get_userchosen();
	int cp = g.get_campaign_status();
	if (esc_just_pressed) item = -1;
	
	switch (menustatus) {
		//hlavni menu
	case 0:
		switch (item) {
		case 0:
			set_menu(1);
			break;
		case 1:
			set_menu(2);
			break;
		case 2:
			set_menu(3);
			break;
		case 3:
			g.create_map();
			break;
		case 4:
			g.save_user();
			g.save_game();
			return false;
		case -1:
			set_menu(0);
			break;
		}
		break;
		//kampan
	case 1:
		switch (item) {
		case 0:
			//posuvnik nahoru
			camp_id--;
			if (camp_id < 0) camp_id = campaign.size() - 1;
			if (camp_id > g.get_campaign_status()) active = false;
			else active = true;
			camp = campaign[camp_id];
			set_menu(1);
			break;
		case 1:
			//zkontroluje mozny pristup do dalsich levelu kampane
			if (camp_id > g.get_campaign_status()) set_menu(1);
			else {
				g.change_mapchosen(maplist_get_mapid(campaign[camp_id]));
				g.go_to_game();
			}
			break;
		case 2:
			//posuvnik dolu
			camp_id++;
			if (camp_id > campaign.size() - 1) camp_id = 0;
			if (camp_id > g.get_campaign_status()) active = false;
			else active = true;
			camp = campaign[camp_id];
			set_menu(1);
			break;
		case -1:
			set_menu(0);
			break;
		}
		break;
		//samostatne mise mimo kampan
	case 2:
		switch (item) {
		case 0:
			set_menu(4);
			break;
		case 1:
			set_menu(5);
			break;
		case 2:
			set_menu(6);
			break;
		case 3:
			set_menu(7);
			break;
		case 4:
			g.go_to_game();
			break;
		case 5:
			set_menu(0);
			break;
		case -1:
			set_menu(0);
			break;
		}
		break;
		//nastaveni
	case 3:
		switch (item) {
		case 0:
			set_menu(8);
			break;
		case 1:
			set_menu(9);
			break;
		case 2:
			set_menu(0);
			break;
		case -1:
			set_menu(0);
			break;
		}
		break;
		//vyber mapy
	case 4:
		switch (item) {
		case 0:
			//posuvnik nahoru
			mapchosen--;
			if (mapchosen < 0) mapchosen = maplist_count() - 1;
			mapname = maplist_get_name(mapchosen);
			while ((mapname[0] == 'm') && 
				(mapname[mapname.length() - 1] > cp)) {
				
				mapchosen--;
				if (mapchosen < 0) 
					mapchosen = maplist_count() - 1;
				mapname = maplist_get_name(mapchosen);
			}
			g.change_mapchosen(mapchosen);
			set_menu(4);
			break;
		case 1:
			set_menu(2);
			break;
		case 2:
			//posuvnik dolu
			mapchosen++;
			if (mapchosen > maplist_count() - 1) mapchosen = 0;
			while ((mapname[0] == 'm') && 
				(mapname[mapname.length() - 1] > cp)) {
				
				mapchosen++;
				if (mapchosen > maplist_count() - 1)
					mapchosen = 0;
				mapname = maplist_get_name(mapchosen);
			}
			g.change_mapchosen(mapchosen);
			set_menu(4);
			break;
		case -1:
			set_menu(2);
			break;
		}
		break;
		//denni doba
	case 5:
		switch (item) {
		case 0:
			//posuvnik nahoru
			dayt_id--;
			if (dayt_id < 0) dayt_id = daytime.size() - 1;
			g.change_daytime(dayt_id);
			dayt = daytime[dayt_id];
			set_menu(5);
			break;
		case 1:
			set_menu(2);
			break;
		case 2:
			//posuvnik dolu
			dayt_id++;
			if (dayt_id > daytime.size() - 1) dayt_id = 0;
			g.change_daytime(dayt_id);
			dayt = daytime[dayt_id];
			set_menu(5);
			break;
		case -1:
			set_menu(2);
			break;
		}
		break;
		//pocasi
	case 6:
		switch (item) {
		case 0:
			//posuvnik nahoru
			weat_id--;
			if (weat_id < 0) weat_id = weather.size() - 1;
			g.change_weather(weat_id);
			weat = weather[weat_id];
			set_menu(6);
			break;
		case 1:
			set_menu(2);
			break;
		case 2:
			//posuvnik dolu
			weat_id++;
			if (weat_id > weather.size() - 1) weat_id = 0;
			g.change_weather(weat_id);
			weat = weather[weat_id];
			set_menu(6);
			break;
		case -1:
			set_menu(2);
			break;
		}
		break;
		//obtiznost hry
	case 7:
		switch (item) {
		case 0:
			//posuvnik nahoru
			diff_id--;
			if (diff_id < 0) diff_id = difficulty.size() - 1;
			g.change_difficulty(diff_id);
			diff = difficulty[diff_id];
			set_menu(7);
			break;
		case 1:
			set_menu(2);
			break;
		case 2:
			//posuvnik dolu
			diff_id++;
			if (diff_id > difficulty.size() - 1) diff_id = 0;
			g.change_difficulty(diff_id);
			diff = difficulty[diff_id];
			set_menu(7);
			break;
		case -1:
			set_menu(2);
			break;
		}
		break;
		//hrac
	case 8:
		switch (item) {
		case 0:
			//pred spustenim randomizeru jmen - prazdno
			name = "";
			set_menu(10);
			break;
		case 1:
			set_menu(11);
			break;
		case 2:
			set_menu(3);
			break;
		case -1:
			set_menu(3);
			break;
		}
		break;
		//nastaveni mysi
	case 9:
		switch (item) {
		case 0:
			//posuvnik nahoru
			sens_id--;
			if (sens_id < 0) sens_id = sensitivities.size() - 1;
			g.change_sensitivity(sens_id);
			sens = sensitivities[sens_id];
			set_menu(9);
			break;
		case 1:
			set_menu(3);
			break;
		case 2:
			//posuvnik dolu
			sens_id++;
			if (sens_id > sensitivities.size() - 1) sens_id = 0;
			g.change_sensitivity(sens_id);
			sens = sensitivities[sens_id];
			set_menu(9);
			break;
		case -1:
			set_menu(3);
			break;
		}
		break;
		//novy hrac
	case 10:
		switch (item) {
		case 0:
			//vygeneruje jmeno pro noveho hrace
			name = get_random_name(1);
			set_menu(10);
			break;
		case 2:
			//kontrola pro nevygenerovane jmeno
			if (name == "") set_menu(10);
			else {
				//pri zvoleni jmena, zaridi vse potrebne
				g.save_user();
				g.change_userchosen(make_user(name));
				username = name;
				if (new_one) {
					set_menu(0);
					new_one = false;
					new_one_plays = true;
				} else set_menu(8);
			}
			break;
		case -1:
			set_menu(8);
			break;
		}
		break;
		//vyber accountu
	case 11:
		switch (item) {
		case 0:
			//posuvnik nahoru
			g.save_user();
			userchosen--;
			if (userchosen < 0) userchosen = userlist_count() - 1;
			g.change_userchosen(userchosen);
			username = userlist_get_name(userchosen);
			set_menu(11);
			break;
		case 1:
			//jmeno uctu k vyberu
			if (username == "") set_menu(11);
			else set_menu(8);
			break;
		case 2:
			//posuvnik dolu
			g.save_user();
			userchosen++;
			if (userchosen > userlist_count() - 1) userchosen = 0;
			g.change_userchosen(userchosen);
			username = userlist_get_name(userchosen);
			set_menu(11);
			break;
		case -1:
			set_menu(8);
			break;
		}
		break;
		//vitezny screen
	case 12:
		set_menu(0);
		if (item == -1) set_menu(0);
		break;
		//prohrany screen
	case 13:
		set_menu(0);
		if (item == -1) set_menu(0);
		break;
	}
	return true;
}

void menu::go_to_winscreen(game& g)
{
	//postup do dalsich levelu kampane
	for (int i = 0;i < campaign.size();++i)
		if (maplist_get_name(g.get_mapchosen()).compare(campaign[i]) 
			== 0) 
			if (i != campaign.size() - 1) 
				g.change_campaign_status(i + 1);
	set_menu(12);
}

void menu::go_to_failscreen()
{
	set_menu(13);
}


bool menu::update(float timediff, bool esc_down, bool left_mouse_down, 
	bool right_mouse_down, int mouse_x, int mouse_y, game& g)
{
	//aktualni hodnoty pro prichod do podmenu
	mapname = maplist_get_name(g.get_mapchosen());
	username = userlist_get_name(g.get_userchosen());
	sens = sensitivities[g.get_sensitivity()];
	dayt = daytime[g.get_daytime()];
	weat = weather[g.get_weather()];
	diff = difficulty[g.get_difficulty()];

	//urceni pozice kurzoru
	cursor_pos += mouse_y;
	if (cursor_pos >= (int)(items.size() *100)) 
		cursor_pos = (int)(items.size() * 100 - 1);
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
	
	//pro vytvoreni prvniho uzivatelskeho uctu pri prvnim spusteni hry
	if ((username == "") && (menustatus != 10)) {
		new_one = true;
		set_menu(10);
	}
	
	//vyber submenu
	if (left_just_pressed || esc_just_pressed)
		if (!handle_menu_click(cursor_pos / 100, g, esc_just_pressed))
			return false;

	return true;
}

void menu::render()
{
	glDisable(GL_DEPTH_TEST);
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 800, 0, 600, 1, -1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glColor3f(1, 0, 1);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	string tmp;

	//uzivatelske jmeno
	if (username != "") {
		glPushMatrix();
		glTranslatef(250, 545, 0);
		tmp = username + "'s";
		username_font->draw(0, 0, tmp.c_str());
		glPopMatrix();
	}

	//nadpis
	glPushMatrix();
	glTranslatef(400, 415, 0);
	title_font->draw(0, 0, "drex");
	glPopMatrix();

	//text pri prvnim vytvareni uzivatelskeho uctu
	if (username == "") {
		glPushMatrix();
		glTranslatef(20, 390, 0);
		white_font->draw(0, 0, "Create your");
		glTranslatef(0, -20, 0);
		white_font->draw(0, 0, "account first.");
		glPopMatrix();
	}
	//a pred prvni hrou
	if (new_one_plays) {
		glPushMatrix();
		glTranslatef(20, 390, 0);
		if (menustatus == 1)
			white_font->draw(0, 0, "Start with the tutorial.");
		else {
			white_font->draw(0, 0, "Start with the tutorial");
			glTranslatef(0, -20, 0);
			white_font->draw(0, 0, "in the campaign submenu.");
		}
		glPopMatrix();
	}

	glPushMatrix();
	glTranslatef(400, 325, 0);
	for (int i = 0;i < items.size();++i) {
		tmp = items[i].first;
		if (cursor_pos / 100 == i)
			tmp = "+ " + tmp + " +";
		if (items[i].second == 1)
			blue_alpha_font->draw(0, 0, tmp.c_str());
		else blue_font->draw(0, 0, tmp.c_str());
		glTranslatef(0, -60, 0);
	}
	glPopMatrix();

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_DEPTH_TEST);
}

