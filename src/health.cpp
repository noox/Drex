
#include <GL/gl.h>
#include <GL/glu.h>

#include "health.h"
#include "world.h"
#include "vector.h"
#include "imageloader.h"

void make_healthstatus(world &w)
{
	float dragon_hp = w.dr.get_hp();
	if (dragon_hp > 100) dragon_hp = 100;
	float dhp = dragon_hp / 100;

	glDepthMask(GL_FALSE);
	glDisable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, 800, 600, 0, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glColor4f(1, 1, 1, 1);

	glEnable(GL_BLEND);

	glTranslatef(397, 80, 0);
	glScalef(3, -3, 0);
	
	glColor4f(0.1, 0.1, 0.1, 0.5);

	//polopruhledny drak v horni casti okna
	//hlava
	glBegin(GL_POLYGON);
	glVertex2f(1, 15);
	glVertex2f(2, 16);
	glVertex2f(1, 18);
	glVertex2f(-1, 18);
	glVertex2f(-2, 16);
	glVertex2f(-1, 15);
	glEnd();
	//telo, ocas a krk draka
	glBegin(GL_POLYGON);
	glVertex2f(0, 0);
	glVertex2f(2, 8);
	glVertex2f(2, 11);
	glVertex2f(1, 13);
	glVertex2f(1, 15);
	glVertex2f(-1, 15);
	glVertex2f(-1, 13);
	glVertex2f(-2, 11);
	glVertex2f(-2, 8);
	glEnd();
	//vrchni cast praveho kridla
	glBegin(GL_POLYGON);
	glVertex2f(2, 8);
	glVertex2f(10.3, 8);
	glVertex2f(10, 9);
	glVertex2f(8, 11);
	glVertex2f(5, 12);
	glVertex2f(2, 11);
	glEnd();
	//vrchni cast leveho kridla
	glBegin(GL_POLYGON);
	glVertex2f(-2, 8);
	glVertex2f(-2, 11);
	glVertex2f(-5, 12);
	glVertex2f(-8, 11);
	glVertex2f(-10, 9);
	glVertex2f(-10.3, 8);
	glEnd();
	//spodni cast praveho kridla
	glBegin(GL_POLYGON);
	glVertex2f(11, 6);
	glVertex2f(10.3, 8);
	glVertex2f(7, 8);
	glEnd();
	//spodni cast leveho kridla
	glBegin(GL_POLYGON);
	glVertex2f(-11, 6);
	glVertex2f(-7, 8);
	glVertex2f(-10.3, 8);
	glEnd();

	glColor4f(1, 0, 0, 1 - dhp);

	//postupne zabarvovani draka od ocasu pri ztrate hp
	if ((dragon_hp <= 90) && (dragon_hp > 80)) {
		//ocas draka
		glBegin(GL_POLYGON);
		glVertex2f(0, 0);
		glVertex2f(1, 3);
		glVertex2f(-1, 3);
		glEnd();
	} else if ((dragon_hp <= 80) && (dragon_hp > 70)) {
		//ocas draka
		glBegin(GL_POLYGON);
		glVertex2f(0, 0);
		glVertex2f(1.2, 5);
		glVertex2f(-1.2, 5);
		glEnd();
	} else if ((dragon_hp <= 70) && (dragon_hp > 60)) {
		//ocas draka
		glBegin(GL_POLYGON);
		glVertex2f(0, 0);
		glVertex2f(1.8, 7);
		glVertex2f(-1.8, 7);
		glEnd();
		//spodni cast praveho kridla
		glBegin(GL_POLYGON);
		glVertex2f(11, 6);
		glVertex2f(10.6, 7);
		glVertex2f(9, 7);
		glEnd();
		//spodni cast leveho kridla
		glBegin(GL_POLYGON);
		glVertex2f(-11, 6);
		glVertex2f(-9, 7);
		glVertex2f(-10.6, 7);
		glEnd();
	} else if ((dragon_hp <= 60) && (dragon_hp > 50)) {
		//telo a ocas draka
		glBegin(GL_POLYGON);
		glVertex2f(0, 0);
		glVertex2f(2, 8);
		glVertex2f(2, 9);
		glVertex2f(-2, 9);
		glVertex2f(-2, 8);
		glEnd();
		//vrchni cast praveho kridla
		glBegin(GL_POLYGON);
		glVertex2f(2, 8);
		glVertex2f(10.3, 8);
		glVertex2f(10, 9);
		glVertex2f(2, 9);
		glEnd();
		//vrchni cast leveho kridla
		glBegin(GL_POLYGON);
		glVertex2f(-2, 8);
		glVertex2f(-2, 9);
		glVertex2f(-10, 9);
		glVertex2f(-10.3, 8);
		glEnd();
		//spodni cast praveho kridla
		glBegin(GL_POLYGON);
		glVertex2f(11, 6);
		glVertex2f(10.3, 8);
		glVertex2f(7, 8);
		glEnd();
		//spodni cast leveho kridla
		glBegin(GL_POLYGON);
		glVertex2f(-11, 6);
		glVertex2f(-7, 8);
		glVertex2f(-10.3, 8);
		glEnd();
	} else if ((dragon_hp <= 50) && (dragon_hp > 40)) {
		//telo a ocas draka
		glBegin(GL_POLYGON);
		glVertex2f(0, 0);
		glVertex2f(2, 8);
		glVertex2f(2, 11);
		glVertex2f(-2, 11);
		glVertex2f(-2, 8);
		glEnd();
		//vrchni cast praveho kridla
		glBegin(GL_POLYGON);
		glVertex2f(2, 8);
		glVertex2f(10.3, 8);
		glVertex2f(10, 9);
		glVertex2f(8, 11);
		glVertex2f(2, 11);
		glEnd();
		//vrchni cast leveho kridla
		glBegin(GL_POLYGON);
		glVertex2f(-2, 8);
		glVertex2f(-2, 11);
		glVertex2f(-8, 11);
		glVertex2f(-10.3, 8);
		glVertex2f(-10, 9);
		glEnd();
		//spodni cast praveho kridla
		glBegin(GL_POLYGON);
		glVertex2f(11, 6);
		glVertex2f(10.3, 8);
		glVertex2f(7, 8);
		glEnd();
		//spodni cast leveho kridla
		glBegin(GL_POLYGON);
		glVertex2f(-11, 6);
		glVertex2f(-7, 8);
		glVertex2f(-10.3, 8);
		glEnd();
	} else if ((dragon_hp <= 40) && (dragon_hp > 30)) {
		//telo a ocas draka
		glBegin(GL_POLYGON);
		glVertex2f(0, 0);
		glVertex2f(2, 8);
		glVertex2f(2, 11);
		glVertex2f(1, 13);
		glVertex2f(-1, 13);
		glVertex2f(-2, 11);
		glVertex2f(-2, 8);
		glEnd();
		//vrchni cast praveho kridla
		glBegin(GL_POLYGON);
		glVertex2f(2, 8);
		glVertex2f(10.3, 8);
		glVertex2f(10, 9);
		glVertex2f(8, 11);
		glVertex2f(5, 12);
		glVertex2f(2, 11);
		glEnd();
		//vrchni cast leveho kridla
		glBegin(GL_POLYGON);
		glVertex2f(-2, 8);
		glVertex2f(-2, 11);
		glVertex2f(-5, 12);
		glVertex2f(-8, 11);
		glVertex2f(-10, 9);
		glVertex2f(-10.3, 8);
		glEnd();
		//spodni cast praveho kridla
		glBegin(GL_POLYGON);
		glVertex2f(11, 6);
		glVertex2f(10.3, 8);
		glVertex2f(7, 8);
		glEnd();
		//spodni cast leveho kridla
		glBegin(GL_POLYGON);
		glVertex2f(-11, 6);
		glVertex2f(-7, 8);
		glVertex2f(-10.3, 8);
		glEnd();
	} else if ((dragon_hp <= 30) && (dragon_hp > 20)) {
		//telo, ocas a krk draka
		glBegin(GL_POLYGON);
		glVertex2f(0, 0);
		glVertex2f(2, 8);
		glVertex2f(2, 11);
		glVertex2f(1, 13);
		glVertex2f(1, 15);
		glVertex2f(-1, 15);
		glVertex2f(-1, 13);
		glVertex2f(-2, 11);
		glVertex2f(-2, 8);
		glEnd();
		//vrchni cast praveho kridla
		glBegin(GL_POLYGON);
		glVertex2f(2, 8);
		glVertex2f(10.3, 8);
		glVertex2f(10, 9);
		glVertex2f(8, 11);
		glVertex2f(5, 12);
		glVertex2f(2, 11);
		glEnd();
		//vrchni cast leveho kridla
		glBegin(GL_POLYGON);
		glVertex2f(-2, 8);
		glVertex2f(-2, 11);
		glVertex2f(-5, 12);
		glVertex2f(-8, 11);
		glVertex2f(-10, 9);
		glVertex2f(-10.3, 8);
		glEnd();
		//spodni cast praveho kridla
		glBegin(GL_POLYGON);
		glVertex2f(11, 6);
		glVertex2f(10.3, 8);
		glVertex2f(7, 8);
		glEnd();
		//spodni cast leveho kridla
		glBegin(GL_POLYGON);
		glVertex2f(-11, 6);
		glVertex2f(-7, 8);
		glVertex2f(-10.3, 8);
		glEnd();
	} else if ((dragon_hp <= 20) && (dragon_hp > 10)) {
		//cast hlavy
		glBegin(GL_POLYGON);
		glVertex2f(1, 15);
		glVertex2f(2, 16);
		glVertex2f(1.5, 17);
		glVertex2f(-1.5, 17);
		glVertex2f(-2, 16);
		glVertex2f(-1, 15);
		glEnd();
		//telo, ocas a krk draka
		glBegin(GL_POLYGON);
		glVertex2f(0, 0);
		glVertex2f(2, 8);
		glVertex2f(2, 11);
		glVertex2f(1, 13);
		glVertex2f(1, 15);
		glVertex2f(-1, 15);
		glVertex2f(-1, 13);
		glVertex2f(-2, 11);
		glVertex2f(-2, 8);
		glEnd();
		//vrchni cast praveho kridla
		glBegin(GL_POLYGON);
		glVertex2f(2, 8);
		glVertex2f(10.3, 8);
		glVertex2f(10, 9);
		glVertex2f(8, 11);
		glVertex2f(5, 12);
		glVertex2f(2, 11);
		glEnd();
		//vrchni cast leveho kridla
		glBegin(GL_POLYGON);
		glVertex2f(-2, 8);
		glVertex2f(-2, 11);
		glVertex2f(-5, 12);
		glVertex2f(-8, 11);
		glVertex2f(-10, 9);
		glVertex2f(-10.3, 8);
		glEnd();
		//spodni cast praveho kridla
		glBegin(GL_POLYGON);
		glVertex2f(11, 6);
		glVertex2f(10.3, 8);
		glVertex2f(7, 8);
		glEnd();
		//spodni cast leveho kridla
		glBegin(GL_POLYGON);
		glVertex2f(-11, 6);
		glVertex2f(-7, 8);
		glVertex2f(-10.3, 8);
		glEnd();
	} else if (dragon_hp <= 10) {
		//hlava
		glBegin(GL_POLYGON);
		glVertex2f(1, 15);
		glVertex2f(2, 16);
		glVertex2f(1, 18);
		glVertex2f(-1, 18);
		glVertex2f(-2, 16);
		glVertex2f(-1, 15);
		glEnd();
		//telo, ocas a krk draka
		glBegin(GL_POLYGON);
		glVertex2f(0, 0);
		glVertex2f(2, 8);
		glVertex2f(2, 11);
		glVertex2f(1, 13);
		glVertex2f(1, 15);
		glVertex2f(-1, 15);
		glVertex2f(-1, 13);
		glVertex2f(-2, 11);
		glVertex2f(-2, 8);
		glEnd();
		//vrchni cast praveho kridla
		glBegin(GL_POLYGON);
		glVertex2f(2, 8);
		glVertex2f(10.3, 8);
		glVertex2f(10, 9);
		glVertex2f(8, 11);
		glVertex2f(5, 12);
		glVertex2f(2, 11);
		glEnd();
		//vrchni cast leveho kridla
		glBegin(GL_POLYGON);
		glVertex2f(-2, 8);
		glVertex2f(-2, 11);
		glVertex2f(-5, 12);
		glVertex2f(-8, 11);
		glVertex2f(-10, 9);
		glVertex2f(-10.3, 8);
		glEnd();
		//spodni cast praveho kridla
		glBegin(GL_POLYGON);
		glVertex2f(11, 6);
		glVertex2f(10.3, 8);
		glVertex2f(7, 8);
		glEnd();
		//spodni cast leveho kridla
		glBegin(GL_POLYGON);
		glVertex2f(-11, 6);
		glVertex2f(-7, 8);
		glVertex2f(-10.3, 8);
		glEnd();
	}

/* 
	//kontura
	glBegin(GL_LINE_STRIP);
	glVertex2f(-1, 18);
	glVertex2f(-2, 16);
	glVertex2f(-1, 15);
	glVertex2f(-1, 13);
	glVertex2f(-2, 11);
	glVertex2f(-5, 12);
	glVertex2f(-8, 11);
	glVertex2f(-10, 9);
	glVertex2f(-11, 6);
	glVertex2f(-7, 8);
	glVertex2f(-2, 8);
	glVertex2f(0, 0);
	glVertex2f(2, 8);
	glVertex2f(7, 8);
	glVertex2f(11, 6);
	glVertex2f(10, 9);
	glVertex2f(8, 11);
	glVertex2f(5, 12);
	glVertex2f(2, 11);
	glVertex2f(1, 13);
	glVertex2f(1, 15);
	glVertex2f(2, 16);
	glVertex2f(1, 18);
	glVertex2f(-1, 18);
	glEnd();
*/

	glDisable(GL_BLEND);

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
}

void make_dragon_hit() 
{
	glDepthMask(GL_FALSE);
	glDisable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, 800, 600, 0, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glColor4f(1, 1, 1, 1);

	glEnable(GL_BLEND);
	glColor4f(1, 0.2, 0.2, 0.7);
	glBegin(GL_QUADS);
	glVertex2f(0, 0);
	glVertex2f(0, 600);
	glVertex2f(800, 600);
	glVertex2f(800, 0);
	glEnd();
	glDisable(GL_BLEND);

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	
}

