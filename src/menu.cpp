
#include <iostream>

using namespace std;

#include "menu.h"

#include "../vendor/OGLFT.h"


void menu::init() {
	face = new OGLFT::TranslucentTexture("data/DK Northumbria.otf",150);
	face2 = new OGLFT::TranslucentTexture("data/DK Northumbria.otf",50);
	face3 = new OGLFT::TranslucentTexture("data/DK Northumbria.otf",30);
	if (face==0||face2==0||!face->isValid()||!face->isValid()) {
    		cerr << "Could not construct face." << endl;
     		return;
	}
	menustatus=0;
}

int left_mouse_hit=0;

bool menu::update(float timediff,bool esc_down,bool left_mouse_down,bool right_mouse_down,int mouse_x,int mouse_y) {
	cursor_pos+=mouse_y;
	if(cursor_pos>399) cursor_pos=399;
	if(cursor_pos<0) cursor_pos=0;
	
	int left_just_pressed=0;
	//proti sekvencim stisknutych tlacitek
	if (left_mouse_down) {
		if (!left_mouse_hit) left_just_pressed=left_mouse_hit=1;
	} else left_mouse_hit=0;
	
	switch (menustatus) { 
		case 0:
			if(cursor_pos/100==0 && left_just_pressed==true) 	
				menustatus=1;
			if(cursor_pos/100==1 && left_just_pressed==true) 	
				menustatus=2;
			if(cursor_pos/100==2 && left_just_pressed==true) 	
				menustatus=3;
			if(cursor_pos/100==3 && left_just_pressed==true) 		
				return false;
			return true;
			break;
		case 1:
			if(cursor_pos/100==3 && left_just_pressed==true) 					menustatus=0;
			return true;
			break;
		case 2:
			if(cursor_pos/100==3 && left_just_pressed==true) 	
				menustatus=0;
			return true;
			break;
		case 3:
			if(cursor_pos/100==3 && left_just_pressed==true) 					menustatus=0;
			return true;
			break;
	}
}

void menu::render() {
	face->setBackgroundColor(1,0,0,0);
	face2->setBackgroundColor(0,0.75,0.75,0);
	face3->setBackgroundColor(0,1,0.5,0);
	face->setForegroundColor(1,0,0,1);
	face2->setForegroundColor(0,0.75,0.75,1);
	face3->setForegroundColor(0,1,0.5,1);
	face->setHorizontalJustification(OGLFT::Face::CENTER);
	face2->setHorizontalJustification(OGLFT::Face::CENTER);
	face3->setHorizontalJustification(OGLFT::Face::CENTER);
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);
	glColor3f(1,0,1);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

	glPushMatrix();
	glTranslatef(400,410,0);
	face->draw(0,0,"drex");
	glPopMatrix();

	switch (menustatus) { 
		case 0:
			glPushMatrix();
			glTranslatef(400,300,0);
			if(cursor_pos/100==0) {face2->draw(-250,0,"+"); face2->draw(250,0,"+");}
			face2->draw(0,0,"campaign");
			glTranslatef(0,-60,0);
			if(cursor_pos/100==1) {face2->draw(-250,0,"+"); face2->draw(250,0,"+");}
			face2->draw(0,0,"missions");
			glTranslatef(0,-60,0);
			if(cursor_pos/100==2) {face2->draw(-250,0,"+"); face2->draw(250,0,"+");}
			face2->draw(0,0,"options");
			glTranslatef(0,-60,0);
			if(cursor_pos/100==3) {face2->draw(-250,0,"+"); face2->draw(250,0,"+");}
			face2->draw(0,0,"exit");
			glPopMatrix();
			break;
		case 1:
			glPushMatrix();
			glTranslatef(400,300,0);
			face2->draw(0,0,"campaign");
			glTranslatef(0,-60,0);
			if(cursor_pos/100==0) {face3->draw(-150,0,"+"); face3->draw(150,0,"+");}
			face3->draw(0,0,"tutorial");
			glTranslatef(0,-30,0);
			if(cursor_pos/100==1) {face3->draw(-150,0,"+"); face3->draw(150,0,"+");}
			face3->draw(0,0,"mission 1");
			glTranslatef(0,-30,0);
			if(cursor_pos/100==2) {face3->draw(-150,0,"+"); face3->draw(150,0,"+");}
			face3->draw(0,0,"mission 2");
			glTranslatef(0,-100,0);
			if(cursor_pos/100==3) {face2->draw(-250,0,"+"); face2->draw(250,0,"+");}
			face2->draw(0,0,"back");

			glPopMatrix();
			break;
		case 2: 
			glPushMatrix();
			glTranslatef(400,300,0);
			face2->draw(0,0,"missions");
			glTranslatef(0,-60,0);
			if(cursor_pos/100==0) {face3->draw(-150,0,"+"); face3->draw(150,0,"+");}
			face3->draw(0,0,"choose the map");
			glTranslatef(0,-30,0);
			if(cursor_pos/100==1) {face3->draw(-150,0,"+"); face3->draw(150,0,"+");}
			face3->draw(0,0,"day time/weather/difficulty");
			glTranslatef(0,-30,0);
			if(cursor_pos/100==2) {face3->draw(-150,0,"+"); face3->draw(150,0,"+");}
			face3->draw(0,0,"play");
			glTranslatef(0,-100,0);
			if(cursor_pos/100==3) {face2->draw(-250,0,"+"); face2->draw(250,0,"+");}
			face2->draw(0,0,"back");

			glPopMatrix();
			break;
		case 3:
			glPushMatrix();
			glTranslatef(400,300,0);
			face2->draw(0,0,"options");
			glTranslatef(0,-60,0);
			if(cursor_pos/100==0) {face3->draw(-150,0,"+"); face3->draw(150,0,"+");}
			face3->draw(0,0,"profile");
			glTranslatef(0,-30,0);
			if(cursor_pos/100==1) {face3->draw(-150,0,"+"); face3->draw(150,0,"+");}
			face3->draw(0,0,"mouse sensitivity");
			glTranslatef(0,-30,0);
			if(cursor_pos/100==2) {face3->draw(-150,0,"+"); face3->draw(150,0,"+");}
			face3->draw(0,0,"...");
			glTranslatef(0,-100,0);
			if(cursor_pos/100==3) {face2->draw(-250,0,"+"); face2->draw(250,0,"+");}
			face2->draw(0,0,"back");

			glPopMatrix();

			break;
	}

	glPushMatrix();
	glTranslatef(400,10,0);
	glScalef(0.3,0.3,1);
	face2->draw(0,0,"player: noox"); //TODO
	glPopMatrix();

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}

