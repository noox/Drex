
#include "GL/gl.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

#include "creation.h"
#include "userlist.h"
#include "maplist.h"

//cast inicializace, nastaveni pro vykreslovaci funkci
void creation::set()
{
	data.resize(6);
	data.clear();

	data[0].r = 0;
	data[0].g = 0.5;
	data[0].b = 1;
	data[0].active = false;
	data[0].name = "water";
	data[0].color = "blue";

	data[1].r = 0;
	data[1].g = 1;
	data[1].b = 0.3;
	data[1].active = false;
	data[1].name = "lowland";
	data[1].color = "green";

	data[2].r = 0.8;
	data[2].g = 0.5;
	data[2].b = 0.1;
	data[2].active = false;
	data[2].name = "upland";
	data[2].color = "brown";

	data[3].r = 1;
	data[3].g = 1;
	data[3].b = 1;
	data[3].active = false;
	data[3].name = "mountain";
	data[3].color = "white";

	data[4].r = 1;
	data[4].g = 0.1;
	data[4].b = 0.1;
	data[4].active = false;
	data[4].name = "estate";
	data[4].color = "red";

	data[5].r = 1;
	data[5].g = 0.1;
	data[5].b = 0.1;
	data[5].active = false;
	data[5].name = "estate";
	data[5].color = "eraser";

	terrain.clear();
	units.clear();
	final_terrain.clear();
	terrain_to_save.clear();
	terrain.resize(8*8);
	units.resize(16*16);
	final_terrain.resize(scale*scale);
	terrain_to_save.resize(scale*scale);

	status = 0;
	go_next = true;
	type = water;
}

void creation::init(game& g)
{
	//nastaveni fontu
	title_font = 
		new OGLFT::TranslucentTexture("data/DK Northumbria.otf", 50);
	grey_font = 
		new OGLFT::TranslucentTexture("data/DK Northumbria.otf", 10);
	white_font = 
		new OGLFT::TranslucentTexture("data/DK Northumbria.otf", 10);
	red_font = 
		new OGLFT::TranslucentTexture("data/DK Northumbria.otf", 10);
	
	if (title_font == 0 || grey_font == 0 || white_font == 0 || 
		red_font == 0 || !title_font->isValid() || 
		!grey_font->isValid() || !white_font->isValid() ||
		!red_font->isValid()) {
		
		cerr << "Could not construct face." << endl;
		return;
	}

	title_font->setForegroundColor(0, 0.75, 0.75, 1);
	title_font->setBackgroundColor(0, 0.75, 0.75, 0);
	title_font->setHorizontalJustification(OGLFT::Face::CENTER);
	grey_font->setForegroundColor(0.8, 0.8, 0.8, 1);
	grey_font->setBackgroundColor(0.8, 0.8, 0.8, 0);
	grey_font->setHorizontalJustification(OGLFT::Face::LEFT);
	white_font->setForegroundColor(1, 1, 1, 1);
	white_font->setBackgroundColor(1, 1, 1, 0);
	white_font->setHorizontalJustification(OGLFT::Face::LEFT);
	red_font->setForegroundColor(1, 0, 0, 1);
	red_font->setBackgroundColor(1, 0, 0, 0);
	red_font->setHorizontalJustification(OGLFT::Face::LEFT);

	scale = 512;
	set();
	left_mouse_hit = 0;
	esc_hit = 0;

	width = g.get_width();
	height = g.get_height();

	x = 90;
	y = 520;
	z = 64;
	zz = 32;

	weather = -1;
	daytime = -1;
	difficulty = -1;
	active_weather = -1;
	active_daytime = -1;
	active_difficulty = -1;
}

void creation::finish()
{
	terrain.clear();
	final_terrain.clear();
	terrain_to_save.clear();
	units.clear();
	data.clear();
}

//typ tlacitka pro stetec kreslici mapu
int creation::get_type()
{
	if ((cursor_pos_x > x + 542) && (cursor_pos_x < x + 542 + 60))
		//4 typy prvku krajiny
		if (status == 0) {
			if ((cursor_pos_y < y - 10) &&
			        (cursor_pos_y > y - 10 - 30))
				type = water;
			if ((cursor_pos_y < y - 10 - 55) &&
			        (cursor_pos_y > y - 10 - 30 - 55))
				type = lowland;
			if ((cursor_pos_y < y - 10 - 2 * 55) &&
			        (cursor_pos_y > y - 10 - 30 - 2 * 55))
				type = upland;
			if ((cursor_pos_y < y - 10 - 3 * 55) &&
			        (cursor_pos_y > y - 10 - 30 - 3 * 55))
				type = mountain;

		//zastavba budov, nebo stetec na mazani
		} else if (status == 1) {
			if ((cursor_pos_y < y - 10) &&
			        (cursor_pos_y > y - 10 - 30))
				type = estate;
			if ((cursor_pos_y < y - 10 - 55) &&
			        (cursor_pos_y > y - 10 - 30 - 55))
				type = no_estate;
		}
}

//blur mapy pro tupejsi hrany terenu
void creation::blur()
{
	int s, rad, k, l;

	rad = 4;
	for (i = 0;i < scale;++i) {
		for (j = 0;j < scale;++j) {
			s = 0;
			for (l = -rad;l <= rad;++l)
				for (k = -rad;k <= rad;++k)
					if ((i + k >= 0) &&
					        (i + k <= scale - 1) &&
					        (j + l >= 0) &&
					        (j + l <= scale - 1))
						s += final_terrain[(i + k) *
							scale + (j + l)];
			terrain_to_save[i*scale+j] =
				s / ((rad * 2 + 1) * (rad * 2 + 1));
		}
	}
}

//ulozi mapu do souboru
void creation::save_map(game& g)
{
	ofstream f;
	string tmp = userlist_get_name(g.get_userchosen()) + "-" + 
		g.get_map_created();
	string tmpp = "maps/" + tmp + ".map";
	f.open(tmpp.c_str());
	
	//vyplni nastaveni mapy
	f << "w\t" << weather << endl << "d\t" << daytime << endl <<
		"f\t" << difficulty << endl;
	
	//vyplni teren
	for (i = 0;i < scale;++i) {
		for (j = 0;j < scale;++j)
			f << terrain_to_save[i * scale + j] << " ";
		f << endl;
	}
	
	//vyplni nepratelske jednotky v meritku - pro jednotky a domy
	for (i = 0;i < 16;++i)
		for (j = 0;j < 16;++j)
			if (units[i * 16 + j] == estate)
				f << j * 16 + 128 << "\t" << i * 16 + 128 << 
					endl;

	//oddelovac
	f << -1 << "\t" << -1 << endl;

	//vyplni prvky krajiny do nizin a pahorkatin
	for (i = 0;i < 8;++i)
		for (j = 0;j < 8;++j)
			if ((terrain[i * 8 + j] == lowland) ||
				(terrain[i * 8 + j] == upland)) {
				
				f << j * 2 * 16 + 128 << "\t" 
					<< i * 2 * 16 + 128 << endl;
				if (FRAND > 0.25) 
					f << (j * 2 + 1) * 16 + 128 << "\t" 
					<< i * 2 * 16 + 128 << endl;
				if (FRAND > 0.5) 
					f << j * 2 * 16 + 128 << "\t" 
					<< (i * 2 + 1) * 16 + 128 << endl;
				if (FRAND > 0.75) 
					f << (j * 2 + 1) * 16 + 128 << "\t" 
					<< (i * 2 + 1) * 16 + 128 << endl;
			}

	f.close();

	//a zresetuje seznam map
	maplist_init();
	g.change_mapchosen(maplist_get_mapid(tmp));
}

//pripravi mapu pro ulozeni
void creation::prepare_map()
{
	int p, k, l, m, n;

	//zvetsi meritko mapy, prida okraje a doplni o finalni hodnoty
	for (i = 0;i < 16;++i)
		for (k = 0;k < 32;++k)
			for (j = 0;j < 16;++j)
				for (l = 0;l < 32;++l) {
					//prida vodu na okraje
					if ((i < 4) || (i > 11) || (j < 4) ||
					        (j > 11)) p = 0;
					
					//a teren mapy
					else p = terrain[(i - 4) * 8 + (j - 4)];
					//hory
					if (p == 3) final_terrain[(((i * 32) +			                        	k) * scale) + j * 32 + l] =
						rand() % 255 + 86;
					//pahorkatiny
					if (p == 2) final_terrain[(((i * 32) +
						k) * scale) + j * 32 + l] =
						rand() % 255 + 1;
					//niziny
					if (p == 1) final_terrain[(((i * 32) +
						k) * scale) + j * 32 + l] =
						rand() % 128 + 1;
					//voda
					if (p == 0) final_terrain[(((i * 32) +
						k) * scale) + j * 32 + l] = 0;
				}
}

//nastaveni hodnot pro zaskrtavatko pocasi/denni doby/obtiznosti
void creation::get_settings()
{
	if ((cursor_pos_x > x + 542) && (cursor_pos_x < x + 542 + 100)) {
		//pocasi
		if ((cursor_pos_y < y - 80) && (cursor_pos_y > y - 90)) {
			weather = 0;
			active_weather = 0;
		}
		if ((cursor_pos_y < y - 100) && (cursor_pos_y > y - 110)) {
			weather = 1;
			active_weather = 1;
		}
		if ((cursor_pos_y < y - 120) && (cursor_pos_y > y - 130)) {
			weather = 2;
			active_weather = 2;
		}
		//denni doba
		if ((cursor_pos_y < y - 170) && (cursor_pos_y > y - 180)) {
			daytime = 0;;
			active_daytime = 3;;
		}
		if ((cursor_pos_y < y - 190) && (cursor_pos_y > y - 200)) {
			daytime = 1;
			active_daytime = 4;
		}
		//obtiznost mise
		if ((cursor_pos_y < y - 240) && (cursor_pos_y > y - 250)) {
			difficulty = 0;
			active_difficulty = 5;
		}
		if ((cursor_pos_y < y - 260) && (cursor_pos_y > y - 270)) {
			difficulty = 1;
			active_difficulty = 6;
		}
		if ((cursor_pos_y < y - 280) && (cursor_pos_y > y - 290)) {
			difficulty = 2;
			active_difficulty = 7;
		}
	}
}

//zkontroluje, zda je na mape nejaky teren
bool creation::terrain_on_map()
{
	for (i = 0;i < 8;++i)
		for (j = 0;j < 8;++j)
			if (terrain[i * 8 + j] > water) return true;
	return false;
}

//zkontroluje, zda jsou na mape nejaci nepratele
bool creation::someone_on_map()
{
	for (i = 0;i < 16;++i)
		for (j = 0;j < 16;++j)
			if (units[i * 16 + j] == estate) return true;
	return false;
}

bool creation::update(float timediff, bool space_down, bool esc_down, 
	bool left_mouse_down, bool right_mouse_down, int mouse__x, 
	int mouse__y, game& g)
{
	//sjednoceni souradnic v okne pro vykreslovani
	cursor_pos_x = mouse__x - (width - 800) / 2;
	cursor_pos_y = 600 - (mouse__y - (height - 600) / 2);
	
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
		data[type].active = false;
		get_type();
		data[type].active = true;
	}

	//screen volby terenu
	if (status == 0) {
		//vyplneni mrizky terenu
		if (left_just_pressed)
			for (i = 0;i < 8;++i) 
				for (j = 0;j < 8;++j)
					//klik na specifickou bunku
					if ((cursor_pos_x > (x - 1) + (j + 1) + 
						(j * (z - 1))) && 
						(cursor_pos_x < (x - 1) + 
						(j + 1) + (j + 1) * (z - 1)) &&
						(cursor_pos_y > (y - 512 - 1) +
						(i + 1) + (i * (z - 1))) && 
						(cursor_pos_y < (y - 512 - 1) +
						(i + 1) + (i + 1) * (z - 1)))
						
						terrain[(7 - i) * 8 + j] = type;

		//tlacitko "continue"
		if (left_just_pressed && (cursor_pos_x > x + 542 - 2) && 
			(cursor_pos_x < x + 542 + 85) && 
			(cursor_pos_y < y - 470 + 5) && 
			(cursor_pos_y > y - 470 - 10 - 5)) {
			
			//pokud neni vyplnen zadny teren, nelze jit dal
			if (!terrain_on_map()) go_next = false;
			else {
				go_next = true;
				status = 1;
				//defaultni stetec
				data[type].active = false;
				type = estate;
				data[estate].active = true;
			}
		}

		//tlacitko "exit"
		if (left_just_pressed && (cursor_pos_x > x + 542 + 88) && 
			(cursor_pos_x < x + 542 + 88 + 50) && 
			(cursor_pos_y < y - 470 + 5) && 
			(cursor_pos_y > y - 470 - 10 - 5)) return false;
	
	//screen pridavani jednotek
	} else if (status == 1) {
		//vyplneni mrizky jednotek
		if (left_just_pressed)
			for (i = 0;i < 16;++i)
				for (j = 0;j < 16;++j)
					//klik na specifickou bunku
					if ((cursor_pos_x > (x - 1) + (j + 1) +
						(j * (zz - 1))) && 
						(cursor_pos_x < (x - 1) + 
						(j + 1) + (j + 1) * (zz - 1)) &&
						(cursor_pos_y > (y - 512 - 1) +
						(i + 1) + (i * (zz - 1))) && 
						(cursor_pos_y < (y - 512 - 1) + 
						(i + 1) + (i + 1) * (zz - 1)))

						units[(15 - i) * 16 + j] = type;

		//tlacitko "continue"
		if (left_just_pressed && (cursor_pos_x > x + 542 - 2) && 
			(cursor_pos_x < x + 542 + 85) && 
			(cursor_pos_y < y - 470 + 5) && 
			(cursor_pos_y > y - 470 - 10 - 5)) {

			//pokud neni vyplnena zadna zastavba, nelze jit dal
			if (!someone_on_map()) go_next = false;
			else {
				go_next = true;
				status = 2;
				//defaultni stetec
				data[type].active = false;
				type = -1;
			}
		}

		//tlacitko "back"
		if (left_just_pressed && (cursor_pos_x > x + 542 + 88) && 
			(cursor_pos_x < x + 542 + 88 + 50) && 
			(cursor_pos_y < y - 470 + 5) && 
			(cursor_pos_y > y - 470 - 10 - 5)) {

			status = 0;
			go_next = true;
			//defaultni stetec
			data[type].active = false;
			type = water;
			data[water].active = true;
		}

	//screen vyberu pocasi/denni doby/obtiznosti
	} else {
		//zaskrtnuti pocasi/denni doby/obtiznosti
		if (left_just_pressed) get_settings();

		//tlacitko "save map"
		if (left_just_pressed && (cursor_pos_x > x + 542 - 2) && 
			(cursor_pos_x < x + 542 + 85) && 
			(cursor_pos_y < y - 470 + 5) && 
			(cursor_pos_y > y - 470 - 10 - 5)) {
			
			//pokud chybi nektere nastaveni, mapa se neulozi
			if ((weather == -1) || (daytime == -1) || 
				(difficulty == -1)) go_next = false;
			else {
				go_next = true;
				prepare_map();
				blur();
				save_map(g);
				set();
				return false;
			}
		}

		//tlacitko "back"
		if (left_just_pressed && (cursor_pos_x > x + 542 + 88) && 
			(cursor_pos_x < x + 542 + 88 + 50) && 
			(cursor_pos_y < y - 470 + 5) && 
			(cursor_pos_y > y - 470 - 10 - 5)) {
			
			status = 1;
			go_next = true;
			//defaultni stetec
			data[type].active = false;
			type = estate;
			data[estate].active = true;
		}
	}

	return true;
}

//nakresli ctverecek ci zaskrtnuty ctverecek, pro volbu vlastnosti mise
void creation::make_quad(int empty)
{
	glPushMatrix();
	glColor3f(0.5, 0.5, 0.5);
	if (empty) glBegin(GL_LINE_LOOP);
	else glBegin(GL_QUADS);
	glVertex2f(0, 0);
	glVertex2f(1, 0);
	glVertex2f(1, 1);
	glVertex2f(0, 1);
	glEnd();
	glPopMatrix();
}

//vykresli sekci pro tvorbu map
void creation::render()
{
	//nastaveni okna
	glDisable(GL_DEPTH_TEST);
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 800, 0, 600, 1, -1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	int a, b;

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glColor3f(1, 0, 1);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//nadpis obsahu okna
	glPushMatrix();
	glTranslatef(400, 540, 0);
	if (status == 0) title_font->draw(0, 0, "create terrain");
	else if (status == 1) title_font->draw(0, 0, "build estate");
	else title_font->draw(0, 0, "choose conditions");
	glPopMatrix();

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);

	//vyplnena mrizka terenu
	glTranslatef(0, 0, 0);
	for (i = 0;i < 8;++i)
		for (j = 0;j < 8;++j) {
			glColor3f(data[terrain[(7 - i) * 8 + j]].r, 
				data[terrain[(7 - i) * 8 + j]].g, 
				data[terrain[(7 - i) * 8 + j]].b);
			glBegin(GL_QUADS);
			glVertex2f((x - 1) + (j + 1) + (j * (z - 1)), 
				(y - 512 - 1) + (i + 1) + (i * (z - 1)));
			glVertex2f((x - 1) + (j + 1) + (j + 1) * (z - 1), 
				(y - 512 - 1) + (i + 1) + (i * (z - 1)));
			glVertex2f((x - 1) + (j + 1) + (j + 1) * (z - 1), 
				(y - 512 - 1) + (i + 1) + (i + 1) * (z - 1));
			glVertex2f((x - 1) + (j + 1) + (j * (z - 1)), 
				(y - 512 - 1) + (i + 1) + (i + 1) * (z - 1));
			glEnd();
		}

	//vyplnena mrizka jednotek
	glTranslatef(0, 0, 0);
	if (status == 1 || status == 2)
		for (i = 0;i < 16;++i)
			for (j = 0;j < 16;++j)
				if (units[(15 - i) * 16 + j] == estate) {
					glColor3f(data[units[(15 - i) * 
						16 + j]].r, data[units[(15 - 
						i) * 16 + j]].g, data[units[(15 
						- i) * 16 + j]].b);
					glBegin(GL_QUADS);
					glVertex2f((x - 1) + (j + 1) + (j * 
						(zz - 1)), (y - 512 - 1) + 
						(i + 1) + (i * (zz - 1)));
					glVertex2f((x - 1) + (j + 1) + (j + 1) *
						(zz - 1), (y - 512 - 1) + (i + 
						1) + (i * (zz - 1)));
					glVertex2f((x - 1) + (j + 1) + (j + 1) *
						(zz - 1), (y - 512 - 1) + (i + 
						1) + (i + 1) * (zz - 1));
					glVertex2f((x - 1) + (j + 1) + (j * 
						(zz - 1)), (y - 512 - 1) + (i +
						1) + (i + 1) * (zz - 1));
					glEnd();
				}

	//mrizka
	if (status == 0) {
		a = z;
		b = 7;
	} else if (status == 1) {
		a = zz;
		b = 15;
	} else {
		a = 2;
		b = 255;
	}
	glColor3f(0.25, 0.25, 0.25);
	glPushMatrix();
	glTranslatef(x, y - a, 0);
	//vodorovne cary
	for (i = 0;i < b;++i) {
		glBegin(GL_LINES);
		glVertex2f(0, 0);
		glVertex2f(511, 0);
		glEnd();
		glTranslatef(0, -a, 0);
	}
	glPopMatrix();

	glPushMatrix();
	glTranslatef(x + a, y - 1, 0);
	//svisle cary
	for (i = 0;i < b;++i) {
		glBegin(GL_LINES);
		glVertex2f(0, 0);
		glVertex2f(0, -511);
		glEnd();
		glTranslatef(a, 0, 0);
	}
	glPopMatrix();

	//tlacitka na volbu stetce
	//v priprave terenu
	if (status == 0) {
		a = 0;
		b = 4;
	
	//v dodani jednotek
	} else if (status == 1) {
		a = 4;
		b = 6;
	}
	if (status != 2) {
		glPushMatrix();
		glTranslatef(x + 542, y - 7, 0);
		for (i = a;i < b;++i) {
			glEnable(GL_TEXTURE_2D);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			//nadpisy stetcu
			if (data[i].active) {
				if (i == no_estate) 
					red_font->draw(0, 0, "eraser");
				else red_font->draw(0, 0, 
					(data[i].name).c_str());
			} else {
				if (i == no_estate) 
					grey_font->draw(0, 0, "eraser");
				else grey_font->draw(0, 0, 
					(data[i].name).c_str());
			}
			glDisable(GL_BLEND);
			glDisable(GL_TEXTURE_2D);

			glTranslatef(0, -3, 0);
			
			//policko stetce
			if (i == no_estate) glColor3f(0, 0, 0);
			else glColor3f(data[i].r, data[i].g, data[i].b);
			glBegin(GL_QUADS);
			glVertex2f(0, 0);
			glVertex2f(0, -30);
			glVertex2f(60, -30);
			glVertex2f(60, 0);
			glEnd();

			//obrys policka stetce
			if (i == no_estate) {
				glBegin(GL_LINE_LOOP);
				glColor3f(data[i].r, data[i].g, data[i].b);
				glVertex2f(0, 0);
				glVertex2f(0, -30);
				glVertex2f(60, -30);
				glVertex2f(60, 0);
				glEnd();
			}

			glTranslatef(0, -52 , 0);
		}
		glPopMatrix();
	}

	//legenda pod stetci
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	if (status == 0) glTranslatef(x + 542, y - 260, 0);
	else if (status == 1) glTranslatef(x + 542, y - 150, 0);
	else glTranslatef(x + 542, y - 10, 0);

	if (status != 2) {
		string tmp = "Use " + data[type].color;
		grey_font->draw(0, 0, tmp.c_str());
		glTranslatef(0, -20, 0);
		if (type == no_estate) grey_font->draw(0, 0, "to remove");
		else grey_font->draw(0, 0, "to arrange");
		glTranslatef(0, -20, 0);
		if (type != water && type != estate && type != no_estate) { 
			tmp = data[type].name + "s.";
			grey_font->draw(0, 0, tmp.c_str());
		} else {
			tmp = data[type].name + ".";
			grey_font->draw(0, 0, tmp.c_str());
		}
	}
	if (status == 2) {
		grey_font->draw(0, 0, "Choose the game");
		glTranslatef(0, -20, 0);
		grey_font->draw(0, 0, "properties.");
	}
	glPopMatrix();

	//volba pocasi/denni doby/obtiznosti
	if (status == 2) {
		//zaskrtavatka
		glDisable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);
		glPushMatrix();
		glTranslatef(x + 542, y - 90, 0);
		glScalef(10, 10, 10);
		for (i = 0; i < 8; ++i) {
			//vyplnene zaskrtavatko
			if (i == active_weather || i == active_daytime || 
				i == active_difficulty) make_quad(false);
			//prazdne zaskrtavatko
			else make_quad(true);
			//posun do dalsi kategorie
			if (i == 2 || i == 4) glTranslatef(0, -5, 0);
			//posun v ramci kategorie
			else glTranslatef(0, -2, 0);
		}
		glPopMatrix();
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//text k zaskrtavatkum
		glPushMatrix();
		glTranslatef(x + 542, y - 70, 0);

		white_font->draw(0, 0, ("weather"));
		glTranslatef(20, -20, 0);
		grey_font->draw(0, 0, ("sunny"));
		glTranslatef(0, -20, 0);
		grey_font->draw(0, 0, ("rainy"));
		glTranslatef(0, -20, 0);
		grey_font->draw(0, 0, ("snowy"));
		glTranslatef(-20, -30, 0);

		white_font->draw(0, 0, ("daytime"));
		glTranslatef(20, -20, 0);
		grey_font->draw(0, 0, ("day"));
		glTranslatef(0, -20, 0);
		grey_font->draw(0, 0, ("night"));
		glTranslatef(-20, -30, 0);

		white_font->draw(0, 0, ("difficulty"));
		glTranslatef(20, -20, 0);
		grey_font->draw(0, 0, ("easy"));
		glTranslatef(0, -20, 0);
		grey_font->draw(0, 0, ("medium"));
		glTranslatef(0, -20, 0);
		grey_font->draw(0, 0, ("hard"));
		glPopMatrix();
	}

	//prostor pro chybovou hlasku
	if (!go_next) {
		glPushMatrix();
		glTranslatef(x + 542, y - 450, 0);
		if (status == 0) {
			grey_font->draw(0, 0, "Fill terrain.");
		} else if (status == 1) {
			grey_font->draw(0, 0, "Add estate.");
		} else {
			glTranslatef(0, 20, 0);
			grey_font->draw(0, 0, "Choose game");
			glTranslatef(0, -20, 0);
			grey_font->draw(0, 0, "properties.");
		}
		glPopMatrix();
	}

	//napisy pro prechody a save
	glPushMatrix();
	glTranslatef(x + 542, y - 480, 0);
	if ((status == 0) || (status == 1)) {
		white_font->draw(0, 0, "continue");
		glTranslatef(90, 0, 0);
		if (status == 0) white_font->draw(0, 0, "exit");
		else white_font->draw(0, 0, "back");
	} else {
		white_font->draw(0, 0, "save map");
		glTranslatef(90, 0, 0);
		white_font->draw(0, 0, "back");
	}
	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();

	glEnable(GL_DEPTH_TEST);
}

