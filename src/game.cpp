
#include "SDL/SDL.h"

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

#include "game.h"
#include "userlist.h"

void game::init(int Width, int Height)
{
	gamestatus = in_menu;
	esc_hit = 0;

	width = Width;
	height = Height;

	mapchosen = 0;
	userchosen = 0;
	sensitivity = 5;
	daytime = day;
	weather = sunny;
	difficulty = easy;

	maplist_init();
	userlist_init();

	load_game();

	m.init();
}

void game::finish()
{
	w.finish();
	m.finish();
	c.finish();
	maplist_finish();
	userlist_finish();
}

bool game::update(float timediff, bool space_down, bool tab_down,
	bool cheat_down,bool esc_down, bool left_mouse_down, 
	bool right_mouse_down, int mouse_x, int mouse_y, int mouse__x, 
	int mouse__y)
{
	int state = playing;

	int esc_just_pressed = 0;
	//proti sekvencim stisknutych tlacitek
	if (esc_down) {
		if (!esc_hit)
			esc_just_pressed = esc_hit = 1;
	} else esc_hit = 0;

	//v menu
	if (gamestatus == in_menu) {
		//chytne a schova kurzor a nastavi rozliseni
		SDL_WM_GrabInput(SDL_GRAB_ON);
		SDL_ShowCursor(SDL_DISABLE);
		glViewport((width - 800) / 2, (height - 600) / 2, 800, 600);
		
		if (!m.update(timediff, esc_down, left_mouse_down, 
			right_mouse_down, mouse_x, mouse_y, *this)) 
			
			return false;
		return true;

	//v tvorbe map
	} else if (gamestatus == in_creation) {
		//pusti a ukaze kurzor a nastavi rozliseni
		SDL_WM_GrabInput(SDL_GRAB_OFF);
		SDL_ShowCursor(SDL_ENABLE);
		glViewport((width - 800) / 2, (height - 600) / 2, 800, 600);

		if (!c.update(timediff, space_down, esc_down, left_mouse_down, 
			right_mouse_down, mouse__x, mouse__y, *this)) 
			
			go_to_menu();
		return true;

	//ve hre
	} else {
		//chytne a schova kurzor, a nastavi rozliseni
		SDL_WM_GrabInput(SDL_GRAB_ON);
		SDL_ShowCursor(SDL_DISABLE);
		glViewport(0, 0, width, height);

		state = w.update(timediff, space_down, tab_down, cheat_down,
			left_mouse_down, right_mouse_down, 
			mouse_x / m.get_sensitivity(sensitivity),
			mouse_y / m.get_sensitivity(sensitivity));
		if (state == win) {
			go_to_menu();
			m.go_to_winscreen(*this);
		} else if (state == fail) {
			go_to_menu();
			m.go_to_failscreen();
		} else if (esc_just_pressed) {
			go_to_menu();
			m.go_to_menu_or_back();
		}
		return true;
	}
}

float game::get_min_timediff()
{
	return 0.02;
}

//vykresluje celou hru
void game::render()
{
	if (gamestatus == in_menu) m.render();
	else if (gamestatus == in_game) w.render();
	else c.render();
}

//nahraje data programu
void game::load_game()
{
	string line;
	fstream f;
	f.open("data/game.txt");
	getline(f, line, '\n');
	stringstream ss(line);
	if (ss) ss >> userchosen;
	f.close();
	read_user_info();
}

//ulozi stav celeho programu
void game::save_game()
{
	ofstream f;
	f.open("data/game.txt");
	f << userchosen << endl;
	f.close();
}

//ulozi uzivatelovo nastaveni
void game::save_user()
{
	if (userlist_get_name(userchosen) == "") return;
	ofstream f;
	f.open(userlist_get_file_name(userchosen).c_str());
	f << "c\t" << campaign_status << endl << "m\t" << mapchosen << endl <<
		"d\t" << daytime << endl << "w\t" << weather << endl <<
		"f\t" << difficulty << endl << "s\t" << sensitivity << endl <<
		"z\t" << maps_created << endl;
	f.close();
}

//nacte z uzivatelskeho souboru nastaveni hry
void game::read_user_info()
{
	if (userlist_get_name(userchosen) == "") return;
	fstream f;
	f.open(userlist_get_file_name(userchosen).c_str());

	char c;
	string line;

	while (getline(f, line, '\n')) {
		stringstream ss(line);
		ss >> c;
		switch (c) {
			//cteni pokroku v kampani
		case 'c':
			ss >> campaign_status;
			break;
			//naposledy vybrana mapa
		case 'm':
			ss >> mapchosen;
			break;
			//naposledy vybrana denni doba
		case 'd':
			ss >> daytime;
			break;
			//naposledy vybrane pocasi
		case 'w':
			ss >> weather;
			break;
			//naposledy vybrana obtiznost hry
		case 'f':
			ss >> difficulty;
			break;
			//naposledy vybrana sensitivita mysi
		case 's':
			ss >> sensitivity;
			break;
			//pocet uzivatelem vytvorenych map
		case 'z':
			ss >> maps_created;
			break;
		}
	}
	f.close();
}

//vrati pocet vytvorenych map uzivatelem a prida udaj o nove
string game::get_map_created()
{
	ostringstream ss;
	ss << maps_created;
	maps_created++;
	ofstream f;
	f.open(userlist_get_file_name(userchosen).c_str());
	f << "c\t" << campaign_status << endl << "m\t" << mapchosen << endl <<
		"d\t" << daytime << endl << "w\t" << weather << endl <<
		"f\t" << difficulty << endl << "s\t" << sensitivity << endl <<
		"z\t" << maps_created << endl;
	f.close();
	return ss.str();
}

//zjisti vlastnosti mise mapy
void game::get_map_data()
{
	fstream f;
	f.open(maplist_get_file_name(mapchosen));

	string line;

	//nacteni nastaveni mapy
	char c;
	for (int i = 0;i < 3;++i) {
		getline(f, line, '\n');
		stringstream ss(line);
		ss >> c;
		switch (c) {
			//zmena pocasi podle nastaveni z mapy
		case 'w':
			ss >> weather;
			break;
			//zmena denni doby podle nastaveni z mapy
		case 'd':
			ss >> daytime;
			break;
			//zmena obtiznosti podle nastaveni z mapy
		case 'f':
			ss >> difficulty;
			break;
		}
	}
	f.close();
}

//zmeni uzivatelske jmeno dle volby accountu a nacte jeho nastaveni
void game::change_userchosen(int Userchosen)
{
	userchosen = Userchosen;
	read_user_info();
}

//vrati userid aktualniho uzivatele
int game::get_userchosen()
{
	return userchosen;
}

//zmeni mapu, dle volby accountu
void game::change_mapchosen(int Mapchosen)
{
	mapchosen = Mapchosen;
	get_map_data();
}

//vrati mapid aktualni mapy
int game::get_mapchosen()
{
	return mapchosen;
}

//zmeni level kampane, podle pokroku uzivatele
void game::change_campaign_status(int Campaign_status)
{
	campaign_status = Campaign_status;
}

//vrati aktualni level kampane
int game::get_campaign_status()
{
	return campaign_status;
}

//zmeni citlivost mysi, dle volby uzivatele
void game::change_sensitivity(int Sensitivity)
{
	sensitivity = Sensitivity;
}

//vrati aktualni sensitivitu mysi
int game::get_sensitivity()
{
	return sensitivity;
}

//zmeni denni dobu hry, dle volby uzivatele
void game::change_daytime(int Daytime)
{
	daytime = Daytime;
}

//vrati aktualni denni dobu hry
int game::get_daytime()
{
	return daytime;
}

//zmeni pocasi hry, dle volby uzivatele
void game::change_weather(int Weather)
{
	weather = Weather;
}

//vrati aktualni pocasi hry
int game::get_weather()
{
	return weather;
}

//zmeni obtiznost hry, dle volby uzivatele
void game::change_difficulty(int Difficulty)
{
	difficulty = Difficulty;
}

//vrati aktualni obtiznost hry
int game::get_difficulty()
{
	return difficulty;
}

//vrati sirku okna
int game::get_width()
{
	return width;
}

//vrati vysku okna
int game::get_height()
{
	return height;
}

