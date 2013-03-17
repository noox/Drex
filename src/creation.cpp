
#include "GL/gl.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

#include "creation.h"

#include "../vendor/OGLFT.h"

void creation::set() {
	data.resize (5);
	data.clear();

	data[0].r = 1;
	data[0].g = 1;
	data[0].b = 1;
	data[0].active = false;
	data[0].name = "mountain";

	data[1].r = 0.8;
	data[1].g = 0.5;
	data[1].b = 0.1;
	data[1].active = false;
	data[1].name = "upland";

	data[2].r = 0;
	data[2].g = 1;
	data[2].b = 0.3;
	data[2].active = false;
	data[2].name = "lowland";

	data[3].r = 0;
	data[3].g = 0.5;
	data[3].b = 1;
	data[3].active = false;
	data[3].name = "water";

	data[4].r = 1;
	data[4].g = 0.1;
	data[4].b = 0.1;
	data[4].active = false;
	data[4].name = "estate";
}

void creation::init() {
	face = new OGLFT::TranslucentTexture ("data/DK Northumbria.otf", 50);
	face2 = new OGLFT::TranslucentTexture ("data/DK Northumbria.otf", 10);
	if (face == 0 || face2 == 0 || !face->isValid() || !face2->isValid() ) {
		cerr << "Could not construct face." << endl;
		return;
	}
	terrain.clear();
	units.clear();
	terrain.resize (8*8);
	units.resize (32*32);

	set();
	status = 0;
	type = -1;
	x = 90;
	y = 520;
	left_mouse_hit = 0;
	esc_hit = 0;
}

int creation::get_type () {
	if (status == 0) {
		if ( (cursor_pos_x > x + 542) && (cursor_pos_x < x + 542 + 60) && (cursor_pos_y < y - 10) && (cursor_pos_y > y - 10 - 30) ) type = mountain;
		if ( (cursor_pos_x > x + 542) && (cursor_pos_x < x + 542 + 60) && (cursor_pos_y < y - 10 - 55) && (cursor_pos_y > y - 10 - 30 - 55) ) type = upland;
		if ( (cursor_pos_x > x + 542) && (cursor_pos_x < x + 542 + 60) && (cursor_pos_y < y - 10 - 2*55) && (cursor_pos_y > y - 10 - 30 - 2*55) ) type = lowland;
		if ( (cursor_pos_x > x + 542) && (cursor_pos_x < x + 542 + 60) && (cursor_pos_y < y - 10 - 3*55) && (cursor_pos_y > y - 10 - 30 - 3*55) ) type = water;
	} else {
		if ( (cursor_pos_x > x + 542) && (cursor_pos_x < x + 542 + 60) && (cursor_pos_y < y - 10) && (cursor_pos_y > y - 10 - 30) ) type = house;
	}
}

bool creation::update (float timediff, bool space_down, bool esc_down, bool left_mouse_down, bool right_mouse_down, int mouse__x, int mouse__y, game& g) {
	cursor_pos_x = mouse__x;
	cursor_pos_y = 600 - mouse__y;

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

	//zmena typu terenu/jednotky
	if (left_just_pressed) {
		if (type != -1) data[type].active = false;
		get_type();
		if (type != -1) data[type].active = true;
	}

	cout << "x: " << cursor_pos_x << " y: " << cursor_pos_y << " type: " << type << " status: " << status << endl;

	if (status == 0) {
		//tlacitko "continue"
		if (left_just_pressed && (cursor_pos_x > x + 542) && (cursor_pos_x < x + 542 + 60 + 5) && (cursor_pos_y < y - 470 + 5) && (cursor_pos_y > y - 470 - 10 - 5) ) status = 1;

	} else {
		//tlacitko "back"
		if (left_just_pressed && (cursor_pos_x > x + 542) && (cursor_pos_x < x + 542 + 60) && (cursor_pos_y < y - 470 + 5) && (cursor_pos_y > y - 470 - 10 - 5) ) status = 0;
		//tlacitko "save map"
		if (left_just_pressed && (cursor_pos_x > x + 542 + 75) && (cursor_pos_x < x + 542 + 60 + 95) && (cursor_pos_y < y - 470 + 5) && (cursor_pos_y > y - 470 - 10 - 5) ) status = 0;
	}

	return true;
}

void creation::render() {
	glDisable (GL_DEPTH_TEST);
	glClearColor (0, 0, 0, 0);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glOrtho (0, 800, 0, 600, 1, -1);
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();

	face->setBackgroundColor (0, 0.75, 0.75, 0);
	face2->setBackgroundColor (0.8, 0.8, 0.8, 0);
	face->setForegroundColor (0, 0.75, 0.75, 1);
	face2->setForegroundColor (0.8, 0.8, 0.8, 1);
	face->setHorizontalJustification (OGLFT::Face::CENTER);
	face2->setHorizontalJustification (OGLFT::Face::LEFT);

	int i, a, b;

	glPixelStorei (GL_UNPACK_ALIGNMENT, 1);

	glColor3f (1, 0, 1);
	glEnable (GL_TEXTURE_2D);
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//nadpis okna
	glPushMatrix();
	glTranslatef (400, 540, 0);
	if (status == 0) face->draw (0, 0, "create terrain");
	else face->draw (0, 0, "add units");
	glPopMatrix();

	glDisable (GL_BLEND);
	glDisable (GL_TEXTURE_2D);

	//oblast mapy
	glPushMatrix();
	glTranslatef (x, y, 0);
	glColor3f (0.1, 0.1, 0.1);
	glBegin (GL_QUADS);
	glVertex2f (0, 0);
	glVertex2f (0, -512);
	glVertex2f (512, -512);
	glVertex2f (512, 0);
	glEnd();
	glPopMatrix();

	//mrizka
	if (status == 0) {
		a = 64;
		b = 7;
	} else {
		a = 16;
		b = 31;
	}
	glColor3f (0.25, 0.25, 0.25);
	glPushMatrix();
	glTranslatef (x, y - a, 0);
	//vodorovne cary
	for (i = 0;i < b;++i) {
		glBegin (GL_LINES);
		glVertex2f (0, 0);
		glVertex2f (512, 0);
		glEnd();
		glTranslatef (0, -a, 0);
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef (x + a, y, 0);
	//svisle cary
	for (i = 0;i < b;++i) {
		glBegin (GL_LINES);
		glVertex2f (0, 0);
		glVertex2f (0, -512);
		glEnd();
		glTranslatef (a, 0, 0);
	}
	glPopMatrix();

	//tlacitka
	//v priprave terenu
	if (status == 0) {
		a = 0;
		b = 4;
		//v dodani jednotek
	} else {
		a = 4;
		b = 5;
	}
	glPushMatrix();
	glTranslatef (x + 542, y - 7, 0);
	for (i = a;i < b;++i) {
		glEnable (GL_TEXTURE_2D);
		glEnable (GL_BLEND);
		glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		if (data[i].active) {
			face2->setBackgroundColor (1, 0, 0, 0);
			face2->setForegroundColor (1, 0, 0, 1);
			face2->draw (0, 0, (data[i].name).c_str() );
			face2->setBackgroundColor (0.8, 0.8, 0.8, 0);
			face2->setForegroundColor (0.8, 0.8, 0.8, 1);
		} else face2->draw (0, 0, (data[i].name).c_str() );
		glDisable (GL_BLEND);
		glDisable (GL_TEXTURE_2D);

		glTranslatef (0, -3, 0);

		glColor3f (data[i].r, data[i].g, data[i].b);
		glBegin (GL_QUADS);
		glVertex2f (0, 0);
		glVertex2f (0, -30);
		glVertex2f (60, -30);
		glVertex2f (60, 0);
		glEnd();

		glTranslatef (0, -52 , 0);
	}
	glPopMatrix();

	//napisy pro prechody a save
	glPushMatrix();
	glTranslatef (x + 542, y - 480, 0);
	glEnable (GL_TEXTURE_2D);
	glEnable (GL_BLEND);
	glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	face2->setBackgroundColor (1, 1, 1, 0);
	face2->setForegroundColor (1, 1, 1, 1);
	if (status == 0) face2->draw (0, 0, "continue");
	else {
		face2->draw (0, 0, "back");
		glTranslatef (75, 0, 0);
		face2->draw (0, 0, "save map");
	}
	glDisable (GL_BLEND);
	glDisable (GL_TEXTURE_2D);
	glPopMatrix();

	//podbarveni kurzoru
	glPushMatrix();

	glPopMatrix();

	glEnable (GL_DEPTH_TEST);
}

