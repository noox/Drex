
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>

using namespace std;

#include "frand.h"
#include "imageloader.h"
#include "health.h"
#include "weather.h"
#include "world.h"

void world::init (int Daytime, int Weather, int Difficulty) {
	dr.init();
	dr.set (vect (10, 10, 10), quat (0.7, 0.7, 0, 0) );
	cam.set (vect (0, 0, 0), quat (1, 0, 0, 0) );
	hm.init();
	hm.load ("data/hm3.png", "data/color3.png");
	es.init();
	ob.init();
	ps.init();
	ms.init();

	tab_hit = 0;
	help_on = false;
	weather = Weather;
	daytime = Daytime;
	difficulty = Difficulty;

	glShadeModel (GL_SMOOTH);
	glFrontFace (GL_CCW);
	glHint (GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glTexEnvf (GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glEnable (GL_DEPTH_TEST);

	//pro nerenderovani veci v pozadi
	glFrontFace (GL_CCW);
	glCullFace (GL_BACK);
	glEnable (GL_CULL_FACE);

	//inicialni nastaveni pro mlhu
	glHint (GL_FOG_HINT, GL_NICEST);
	f.set_color (0.4, 0.6, 0.9);
	f.set_distance (50, 200);

	float hm_x, hm_y;
	hm.get_sizes (hm_x, hm_y);
	//domy
	for (int i = 0;i < 8;++i) {
		enemy& p = es.add_one();
		p.pos.x = (0.13 + FRAND * 0.07) * hm_x;
		p.pos.y = (0.13 + FRAND * 0.07) * hm_y;
		p.pos.z = hm.get_height (p.pos.x, p.pos.y);
		p.size_x = 3 + FRAND;
		p.size_y = 3 + FRAND;
		p.size_z = 3 + FRAND;
		p.roof_size = 5 * FRAND;
		p.rot = 360 * FRAND;
	}
	for (int i = 0;i < 20;++i) {
		enemy& p = es.add_one();
		p.pos.x = (0.3 + FRAND * 0.1) * hm_x;
		p.pos.y = (0.3 + FRAND * 0.1) * hm_y;
		p.pos.z = hm.get_height (p.pos.x, p.pos.y);
		p.size_x = 3 + FRAND;
		p.size_y = 3 + FRAND;
		p.size_z = 3 + FRAND;
		p.roof_size = 5 * FRAND;
		p.rot = 360 * FRAND;
	}
	for (int i = 0;i < 5;++i) {
		enemy& p = es.add_one();
		p.pos.x = (0.13 + FRAND * 0.05) * hm_x;
		p.pos.y = (0.3 + FRAND * 0.05) * hm_y;
		p.pos.z = hm.get_height (p.pos.x, p.pos.y);
		p.size_x = 3 + FRAND;
		p.size_y = 3 + FRAND;
		p.size_z = 3 + FRAND;
		p.roof_size = 5 * FRAND;
		p.rot = 360 * FRAND;
	}
	//lide
	for (int i = 0;i < 20;++i) {
		object& p = ob.add_one();
		p.spd.x = DFRAND;
		p.spd.y = DFRAND;
		p.spd.z = 0;
		p.size = 1 + FRAND;
		p.start_pos.x = (0.13 + FRAND * 0.07) * hm_x;
		p.start_pos.y = (0.13 + FRAND * 0.07) * hm_y;
		p.start_pos.z = hm.get_height (p.pos.x, p.pos.y);
		p.pos.x = p.start_pos.x;
		p.pos.y = p.start_pos.y;
		p.pos.z = p.start_pos.z;
		p.type = object_person;
		p.hp = 10;
	}
	//listnate stromy
	for (int i = 0;i < 10;++i) {
		object& p = ob.add_one();
		p.spd = vect (0, 0, 0);
		p.size = 4 + FRAND;
		p.pos.x = (0.13 + FRAND * 0.07) * hm_x;
		p.pos.y = (0.13 + FRAND * 0.07) * hm_y;
		p.pos.z = hm.get_height (p.pos.x, p.pos.y);
		p.type = object_tree1;
		p.hp = 50;
	}
	//jehlicnate stromy
	for (int i = 0;i < 10;++i) {
		object& p = ob.add_one();
		p.spd = vect (0, 0, 0);
		p.size = 4 + FRAND;
		p.pos.x = (0.13 + FRAND * 0.07) * hm_x;
		p.pos.y = (0.13 + FRAND * 0.07) * hm_y;
		p.pos.z = hm.get_height (p.pos.x, p.pos.y);
		p.type = object_tree2;
		p.hp = 50;
	}
	//kere
	for (int i = 0;i < 10;++i) {
		object& p = ob.add_one();
		p.spd = vect (0, 0, 0);
		p.size = 1 + FRAND;
		p.pos.x = (0.13 + FRAND * 0.07) * hm_x;
		p.pos.y = (0.13 + FRAND * 0.07) * hm_y;
		p.pos.z = hm.get_height (p.pos.x, p.pos.y);
		p.type = object_tree3;
		p.hp = 50;
	}
/*	{object& p = ob.add_one();
		p.spd.x = 0;
		p.spd.y = 0;
		p.spd.z = 0;
		p.size = 20 + FRAND;
		p.start_pos.x = 10;
		p.start_pos.y = 10;
		p.start_pos.z = hm.get_height (p.pos.x, p.pos.y);
		p.pos.x = p.start_pos.x;
		p.pos.y = p.start_pos.y;
		p.pos.z = p.start_pos.z;
		p.type = object_person;
		p.hp = 10;
		};
*/
}

void world::finish() {
	hm.finish();
	dr.finish();
	es.finish();
	ob.finish();
	ps.finish();
	ms.finish();
}

int world::update (float timediff, bool space_down, bool tab_down, bool esc_down, bool left_mouse_down, bool right_mouse_down, int mouse_x, int mouse_y) {
	dr.update (mouse_x, mouse_y, left_mouse_down, right_mouse_down, space_down, timediff, *this);
	es.update (timediff, *this);
	ob.update (timediff, *this);
	ps.update (timediff);
	ms.update (timediff, *this);
	cam.follow_ori (dr.ori, 0.01, timediff);
	cam.follow_pos (dr.camera_pos(), 0.1, timediff);
	cam.collide_with_heightmap (hm);

	int tab_just_pressed = 0;
	//proti sekvencim stisknutych tlacitek
	if (tab_down) {
		if (!tab_hit)
			tab_just_pressed = tab_hit = 1;
	} else tab_hit = 0;
	//pro navigaci po mape k nepriteli
	if (tab_just_pressed) help_on = true;

	if (daytime == night) f.set_color (0, 0, 0);

	//pro ukonceni hry vyhrou
	if (es.all_enemies_dead() ) return win;
	//pro ukonceni hry prohrou
	if (dr.dead() ) return fail;

	return playing;
}

void world::render() {
	glClearColor (0, 0, 0, 0);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	gluPerspective (90, 1.33333, 0.1, 1000);
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();

	cam.set_gl();

	//noc X den
	if (daytime == night) skyb.draw (cam.pos, true);
	else skyb.draw (cam.pos, false);

	glEnable (GL_LIGHTING);
	glEnable (GL_LIGHT0);
	glEnable (GL_COLOR_MATERIAL);
	{
		float light_direction[] = {0.4082, 0.4082, 0.8165, 0};
		if (daytime == night) light_direction[3] = 0.5;
		glLightfv (GL_LIGHT0, GL_POSITION, light_direction);
	}
	f.turn_on();
	dr.draw();
	hm.draw();
	es.draw();
	ob.draw(*this);

	if (weather == rainy) make_rain (*this);
	if (weather == snowy) make_snow (*this);

	ms.draw();
	f.turn_off();

	glDisable (GL_LIGHTING);
	ps.draw (*this);

	//navigace k nepriteli
	if (help_on) {
		vect en = es.one_enemy();

		//nakresleni bile cary k nepriteli
		glPushMatrix();
		glColor3f (1, 1, 1);
		glBegin (GL_LINES);
		glVertex3f (dr.pos.x, dr.pos.y, dr.pos.z);
		glVertex3f (en.x, en.y, en.z);
		glEnd();
		glPopMatrix;
		help_on = false;
	}
}

