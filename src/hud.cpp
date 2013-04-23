
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>

using namespace std;

#include "hud.h"
#include "world.h"
#include "vector.h"
#include "imageloader.h"

void hud::init()
{
	white_font = 
		new OGLFT::TranslucentTexture("data/DK Northumbria.otf", 10);
	if (white_font == 0 || !white_font->isValid()) {
		cerr << "Could not construct face." << endl;
		return;
	}

	white_font->setBackgroundColor(1, 1, 1, 0);
	white_font->setForegroundColor(1, 1, 1, 1);
	white_font->setHorizontalJustification(OGLFT::Face::CENTER);

	counter = 0;
}

void hud::beginning()
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
}

void hud::ending()
{
	glDisable(GL_BLEND);

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
}

void hud::make_healthstatus(float dragon_hp)
{
	if (dragon_hp > 100) dragon_hp = 100;
	float dhp = dragon_hp / 100;

	beginning();

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
	ending();
}

void hud::make_dragon_hit() 
{
	beginning();

	glColor4f(1, 0.2, 0.2, 0.7);
	glBegin(GL_QUADS);
	glVertex2f(0, 0);
	glVertex2f(0, 600);
	glVertex2f(800, 600);
	glVertex2f(800, 0);
	glEnd();
	
	ending();
}

void hud::draw_tutorial()
{
	int x = 500;

	beginning();

	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glTranslatef(400, 100, 0);
	glScalef(1, -1, 1);
	
	if ((counter >= 50) && (counter < x))
		white_font->draw(0, 0, "Welcome to the drex!");

	if ((counter >= x + 10) && (counter < 2 * x)) {
		white_font->draw(0, 0, "Use your mouse to control the dragon.");
		if (counter >= x + 100) {
			glTranslatef(0, -20, 0);
			white_font->draw(0, 0, "Use it as a pilot uses yoke.");
			glTranslatef(0, 20, 0);
		}
	}

	if ((counter >= 2 * x + 10) && (counter < 3 * x))
		white_font->draw(0, 0, "Space bar will speed you up.");
	
	if ((counter >= 3 * x + 50) && (counter < 4 * x)) {
		white_font->draw(0, 0, "What to do now?");
		if (counter >= 3 * x + 150) {
			glTranslatef(0, -20, 0);
			white_font->draw(0, 0, "Better find the enemies!");
			//TODO story part
			glTranslatef(0, 20, 0);
		}
	}	

	if ((counter >= 4 * x + 10) && (counter < 5 * x))
		white_font->draw(0, 0, "Hit the Tab key for some navigation.");
	
	if ((counter >= 5 * x + 10) && (counter < 7 * x)) {
		white_font->draw(0, 0, "Use the left mouse button to shoot fire.");
		if (counter >= 6 * x) {
			glTranslatef(0, -20, 0);
			white_font->draw(0, 0, "..or the right mouse button for a stronger fireball.");
			glTranslatef(0, 20, 0);
		}
	}

	if ((counter >= 7 * x + 10) && (counter < 8 * x))
		white_font->draw(0, 0, "To win, you only need to destroy the houses.");

	if ((counter >= 9 * x) && (counter < 10 * x + 200)) {
		white_font->draw(0, 0, "Beware of enemies' missiles.");
		if (counter >= 9 * x + 200) {
			glTranslatef(0, -20, 0);
			white_font->draw(0, 0, "Monitor your health");
			glTranslatef(0, -20, 0);
			white_font->draw(0, 0, "by checking the little dragon up here.");
			glTranslatef(0, 40, 0);
		}
	}

	if ((counter >= 11 * x) && (counter < 12 * x)) 
		white_font->draw(0, 0, "Enjoy the game!");

	glDisable(GL_TEXTURE_2D);
	ending();

	if (counter < 12 * x) counter++;
}

