
#include "SDL/SDL.h"
#include <iostream>

using namespace std;

#include "game.h"

#include "world.h"
#include "menu.h"
#include "maplist.h"
#include "userlist.h"

void game::init() {
	gamestatus = in_menu;
	esc_hit = 0;
	mapchosen = 0;
	userchosen = 0;
	sensitivity = 4;
	daytime = day;
	weather = sunny;
	difficulty = easy;
	w.init (daytime, weather, difficulty);
	m.init();
	c.init();
	maplist_init();
	userlist_init();
}

void game::finish() {
	w.finish();
}

bool game::update (float timediff, bool space_down, bool tab_down, bool esc_down, bool left_mouse_down, bool right_mouse_down, int mouse_x, int mouse_y, int mouse__x, int mouse__y) {
	int state = playing;

	int esc_just_pressed = 0;
	//proti sekvencim stisknutych tlacitek
	if (esc_down) {
		if (!esc_hit)
			esc_just_pressed = esc_hit = 1;
	} else esc_hit = 0;

	//v menu
	if (gamestatus == in_menu) {
		SDL_ShowCursor (SDL_DISABLE);
		if (!m.update (timediff, esc_down, left_mouse_down, right_mouse_down, mouse_x, mouse_y, *this) ) return false;
		return true;

	//v tvorbe map
	} else if (gamestatus == in_creation) {
		SDL_ShowCursor (SDL_ENABLE);
		c.update (timediff, space_down, esc_down, left_mouse_down, right_mouse_down, mouse__x, mouse__y, *this);
		if (esc_just_pressed) go_to_menu();
		return true;

	//ve hre
	} else {
		SDL_ShowCursor (SDL_DISABLE);
		state = w.update (timediff, space_down, tab_down, esc_down, left_mouse_down, right_mouse_down, mouse_x / sensitivity, mouse_y / sensitivity);
		if (state == win) {
			go_to_menu();
			m.go_to_winscreen();
		} else if (state == fail) {
			go_to_menu();
			m.go_to_failscreen();
		} else if (esc_just_pressed) go_to_menu();
		return true;
	}
}

float game::get_min_timediff() {
	return 0.02;
}

void game::render() {
	if (gamestatus == in_menu) m.render();
	else if (gamestatus == in_game) w.render();
	else c.render();
}

//zmeni uzivatelske jmeno, dle volby accountu
void game::change_userchosen (int Userchosen) {
	userchosen = Userchosen;
}

//vrati userid aktualniho uzivatele
int game::get_userchosen() {
	return userchosen;
}

//zmeni mapu, dle volby accountu
void game::change_mapchosen (int Mapchosen) {
	mapchosen = Mapchosen;
}

//vrati maprid aktualni mapy
int game::get_mapchosen() {
	return mapchosen;
}

//zmeni citlivost mysi, dle volby uzivatele
void game::change_sensitivity (int Sensitivity) {
	sensitivity = Sensitivity;
}

//vrati aktualni sensitivitu mysi
int game::get_sensitivity() {
	return sensitivity;
}

//zmeni denni dobu hry, dle volby uzivatele
void game::change_daytime (int Daytime) {
	daytime = Daytime;
}

//vrati aktualni denni dobu hry
int game::get_daytime() {
	return daytime;
}

//zmeni pocasi hry, dle volby uzivatele
void game::change_weather (int Weather) {
	weather = Weather;
}

//vrati aktualni pocasi hry
int game::get_weather() {
	return weather;
}

//zmeni obtiznost hry, dle volby uzivatele
void game::change_difficulty (int Difficulty) {
	difficulty = Difficulty;
}

//vrati aktualni obtiznost hry
int game::get_difficulty() {
	return difficulty;
}

