
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>

using namespace std;

#include "world.h"
#include "frand.h"
#include "imageloader.h"
#include "weather.h"
#include "maplist.h"

void world::init(game &g)
{
	snd.init();
	dr.init();
	skyb.init();

	//random pozice draka na pocatku
	int px = hm.get_size(FRAND * 255 + 128);
	int py = hm.get_size(FRAND * 255 + 128);
	int pz = hm.get_height(px, py) + 50;
	dr.set(vect(px, py, pz), quat(0.7, 0.7, 0, 0));

	cam.set(vect(px - 10, py - 10, pz - 10), quat(1, 0, 0, 0));

	hm.init(g, *this);
	es.init();
	ob.init();
	ps.init();
	ms.init();
	h.init(*this);

	cu = 8;
	rad = 70;

	hm.load(maplist_get_file_name(g.get_mapchosen()), g, *this);

	//pokud je zvolen tutorial
	if (maplist_get_name(g.get_mapchosen())[0] == 't') tutorial = true;
	else tutorial = false;

	tab_hit = 0;
	cheat = false;
	help_on = false;
	dragon_hit = 0;
	weather = g.get_weather();

	if (weather == rainy) snd.play_rain(dr);
	if (weather == sunny) snd.play_wind(dr);

	daytime = g.get_daytime();
	difficulty = g.get_difficulty();

	width = g.get_width();
	height = g.get_height();

	//inicialni nastaveni pro mlhu
	glHint(GL_FOG_HINT, GL_NICEST);
	//zmeni barvu mlhy v noci
	if (daytime == night) f.set_color(0, 0, 0);
	else f.set_color(0.4, 0.6, 0.9);
	f.set_distance(80, 200);

	glShadeModel(GL_SMOOTH);
	glFrontFace(GL_CCW);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glEnable(GL_DEPTH_TEST);

	//pro nerenderovani veci v pozadi
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);
}

void world::finish()
{
	snd.finish();
	hm.finish();
	skyb.finish();
	dr.finish();
	es.finish();
	ob.finish();
	ps.finish();
	ms.finish();
}

int world::update(float timediff, bool space_down, bool tab_down,
	bool cheat_down, bool esc_down, bool left_mouse_down, 
	bool right_mouse_down, int mouse_x, int mouse_y)
{
	//aktualizace podmodulu
	dr.update(mouse_x, mouse_y, left_mouse_down, right_mouse_down,
		space_down, timediff, *this);
	es.update(timediff, *this);
	ob.update(timediff, *this);
	ps.update(timediff);
	ms.update(timediff, *this);
	cam.follow_ori(dr.ori, 0.01, timediff);
	cam.follow_pos(dr.camera_pos(), 0.1, timediff);
	cam.collide_with_heightmap(hm);

	int tab_just_pressed = 0, cheat_just_pressed = 0;
	//proti sekvencim stisknutych tlacitek
	if (tab_down) {
		if (!tab_hit) tab_just_pressed = tab_hit = 1;
	} else tab_hit = 0;
	if (cheat_down) {
		if (!cheat_hit) cheat_just_pressed = cheat_hit = 1;
	} else cheat_hit = 0;

	//pro navigaci po mape k nepriteli
	if (tab_just_pressed) help_on = true;

	//zapnuti/vypnuti hracovy nesmrtelnosti
	if (cheat_just_pressed) {
		if (cheat) cheat = false;
		else cheat = true;
	}

	//pro ukonceni hry vyhrou
	if (es.all_enemies_dead()) return win;
	//pro ukonceni hry prohrou
	if (dr.dead()) return fail;

	return playing;
}

void world::render()
{
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, 1.33333, 0.1, 1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	cam.set_gl();

	//noc X den
	if (daytime == night) skyb.draw(cam.pos, true);
	else skyb.draw(cam.pos, false);

	//zapnuti a nastaveni svetla
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	{
		float light_direction[] = {0.4082, 0.4082, 0.8165, 0};
		if (daytime == night) light_direction[3] = 0.5;
		glLightfv(GL_LIGHT0, GL_POSITION, light_direction);
	}
	//mlha
	f.turn_on();

	//vykresleni podmodulu
	dr.draw(*this);
	hm.draw();
	es.draw(*this);
	ob.draw(*this);

	//pokud prsi nebo snezi
	if (weather == rainy) make_rain(*this);
	if (weather == snowy) make_snow(*this);

	f.turn_off();

	glDisable(GL_LIGHTING);
	
	//navigace k nepriteli
	if (help_on) {
		vect en = es.one_enemy();

		//nakresleni bile cary k nepriteli
		glPushMatrix();
		glColor3f(1, 1, 1);
		glBegin(GL_LINES);
		glVertex3f(dr.pos.x, dr.pos.y, dr.pos.z);
		glVertex3f(en.x, en.y, en.z);
		glEnd();
		glPopMatrix;

		help_on = false;
	}

	ms.draw(*this);
	ps.draw(*this);
	
	//2D hud pres obrazovku informujici o hp draka
	h.make_healthstatus(dr.get_hp());	
	
	//screen cervene problikne pri zasahu draka neprateli
	if (dragon_hit > 0) {
		h.make_dragon_hit();
		dragon_hit--;
	}

	//pokud je zapnuty cheat, pise o tom na screen
	if (cheat) h.draw_cheat();

	//v tutorialu zobrazuje napovedu
	if (tutorial) h.draw_tutorial();
}

//prida domy a jednotky
void world::add_enemy(float u, float v)
{
	//domy
	for (int i = 0;i < cu;++i) {
		enemy& p = es.add_one();
		p.pos.x = u + FRAND * rad;
		p.pos.y = v + FRAND * rad;
		p.pos.z = hm.get_height(p.pos.x, p.pos.y);
		p.size_x = 3 + FRAND;
		p.size_y = 3 + FRAND;
		p.size_z = 3 + FRAND;
		p.roof_size = 5 * FRAND;
		p.rot = 360 * FRAND;
	}

	//lide
	for (int i = 0;i < cu;++i) {
		object& p = ob.add_one();
		p.spd.x = DFRAND;
		p.spd.y = DFRAND;
		p.spd.z = 0;
		p.size = 1 + FRAND;
		p.start_pos.x = u + FRAND * rad;
		p.start_pos.y = v + FRAND * rad;
		p.start_pos.z = hm.get_height(p.pos.x, p.pos.y);
		p.pos.x = p.start_pos.x;
		p.pos.y = p.start_pos.y;
		p.pos.z = p.start_pos.z;
		p.type = object_person;
		p.hp = 10;
	}
}

//prida objekty nedulezite pro logiku hry (stromy)
void world::add_rest(float u, float v)
{
	//listnate stromy
	for (int i = 0;i < cu;++i) {
		object& p = ob.add_one();
		p.spd = vect(0, 0, 0);
		p.size = 4 + FRAND;
		p.pos.x = u + FRAND * rad;
		p.pos.y = v + FRAND * rad;
		p.pos.z = hm.get_height(p.pos.x, p.pos.y);
		p.type = object_tree1;
		p.hp = 50;
	}
	//jehlicnate stromy
	for (int i = 0;i < cu;++i) {
		object& p = ob.add_one();
		p.spd = vect(0, 0, 0);
		p.size = 4 + FRAND;
		p.pos.x = u + FRAND * rad;
		p.pos.y = v + FRAND * rad;
		p.pos.z = hm.get_height(p.pos.x, p.pos.y);
		p.type = object_tree2;
		p.hp = 50;
	}
	//kere
	for (int i = 0;i < cu;++i) {
		object& p = ob.add_one();
		p.spd = vect(0, 0, 0);
		p.size = 1 + FRAND;
		p.pos.x = u + FRAND * rad;
		p.pos.y = v + FRAND * rad;
		p.pos.z = hm.get_height(p.pos.x, p.pos.y);
		p.type = object_tree3;
		p.hp = 50;
	}
}

//na zaklade zniceneho domu upravi pocet jednotek
void world::remove_object(int c)
{
	ob.delete_object(c);
}

//meni promennou pro efekt pri zasahu draka pro render
void world::dragon_damaged()
{
	dragon_hit = 5;
}

//pokud je zapnuty cheat nesmrtelnosti
bool world::cheating()
{
	if (cheat) return true;
	return false;
}

//vrati sirku okna
int world::get_width()
{
	return width;
}

//vrati vysku okna
int world::get_height()
{
	return height;
}

