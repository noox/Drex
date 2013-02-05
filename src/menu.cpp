
#include <iostream>
#include <vector>
#include <string>

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
	left_mouse_hit=0;
	esc_hit=0;
	set_menu(0);
}

void menu::set_menu(int newstatus) {
	menustatus=newstatus;
	items.clear();
	switch (newstatus) {
		//hlavni menu
		case 0:
			items.push_back("campaign");
			items.push_back("missions");
			items.push_back("options");
			items.push_back("exit");
			break;
		//kampan
		case 1:
			items.push_back("tutorial");
			items.push_back("mission 1");
			items.push_back("mission 2");
			items.push_back("back");
			break;
		//jednotlive mise
		case 2:
			items.push_back("choose map");
			items.push_back("day time");
			items.push_back("weather");
			items.push_back("difficulty");
			items.push_back("back");
			break;
		//nastaveni
		case 3:
			items.push_back("player");
			items.push_back("mouse sensitivity");
			items.push_back("back");
			break;
		//vitezny screen
		case 4:
			items.push_back("victory");
			break;
	}
	cursor_pos=0;
}

bool menu::handle_menu_click(int item,game& g,int esc_just_pressed) {
	if(esc_just_pressed) item=-1;
	cout << item << endl;
	switch (menustatus) {
		//hlavni menu
		case 0:
			switch (item) {
				case 0: set_menu(1); break;
				case 1: set_menu(2); break;
				case 2: set_menu(3); break;
				case 3: return false; 
				case -1: return false;
			}
			break;
		//kampan
		case 1:
			switch (item) {
				case 0: g.go_to_game(); break;
				case 3: set_menu(0); break; //TODO esc??
				case -1: set_menu(0); break;
			}
			break;
		//jednotlive mise
		case 2:
			switch (item) {
				case 4: set_menu(0); break;
				case -1: set_menu(0); break;
			}
			break;
		//nastaveni
		case 3:
			switch (item) {
				case 2: set_menu(0); break;
				case -1: set_menu(0); break;
			}
			break;
		//vitezny screen
		case 4:
			set_menu(0);
			case -1: set_menu(0); break;
			break;
		//TODO zbytek polozek

	}
	return true;
}

void menu::go_to_winscreen() {
	set_menu(4);
}

bool menu::update(float timediff,bool esc_down,bool left_mouse_down,bool right_mouse_down,int mouse_x,int mouse_y,game& g) {
	//urceni pozice kurzoru
	cursor_pos+=mouse_y;
	if(cursor_pos>=(int)(items.size()*100)) cursor_pos=(int)(items.size()*100-1);
	if(cursor_pos<0) cursor_pos=0;

	int left_just_pressed=0,esc_just_pressed=0;
	//proti sekvencim stisknutych tlacitek
	if (left_mouse_down) {
		if (!left_mouse_hit)
			left_just_pressed=left_mouse_hit=1;
	} else left_mouse_hit=0;
	if (esc_down) {
		if (!esc_hit)
			esc_just_pressed=esc_hit=1;
	} else esc_hit=0;

	//vyber submenu
	if(left_just_pressed||esc_just_pressed)
		if(!handle_menu_click(cursor_pos/100,g,esc_just_pressed))
			return false;

	return true;
}

void menu::render() {
	glDisable(GL_DEPTH_TEST);
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,800,0,600,1,-1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

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

	glPushMatrix();
	glTranslatef(400,300,0);
	for(int i=0;i<items.size();++i) {
		string t=items[i];
		if(cursor_pos/100==i)
			t="+ "+t+" +";
		face2->draw(0,0,t.c_str());
		glTranslatef(0,-60,0);
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(400,10,0);
	glScalef(0.3,0.3,1);
	face2->draw(0,0,"player: noox"); //TODO
	glPopMatrix();

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);

	glEnable(GL_DEPTH_TEST);
}

