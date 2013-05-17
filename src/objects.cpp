
#include <GL/gl.h>
#include <iostream>

using namespace std;

#include "objects.h"
#include "world.h"
#include "imageloader.h"

//inicializace stromu a lidi
void object_system::init()
{
	objects.clear();

	//textura listnatych stromu
	tex_tree1 = imageloader_load("data/tree1.png", 4, GL_RGBA);
	glBindTexture(GL_TEXTURE_2D, tex_tree1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	//textura jehlicnatych stromu
	tex_tree2 = imageloader_load("data/tree2.png", 4, GL_RGBA);
	glBindTexture(GL_TEXTURE_2D, tex_tree2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	//textura keru
	tex_tree3 = imageloader_load("data/tree3.png", 4, GL_RGBA);
	glBindTexture(GL_TEXTURE_2D, tex_tree3);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	//textura zasnezenych jehlicnatych stromu
	tex_snowy_tree2 = imageloader_load("data/snowy-tree2.png", 4, GL_RGBA);
	glBindTexture(GL_TEXTURE_2D, tex_snowy_tree2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	//textura zasnezenych keru
	tex_snowy_tree3 = imageloader_load("data/snowy-tree3.png", 4, GL_RGBA);
	glBindTexture(GL_TEXTURE_2D, tex_snowy_tree3);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	//textura jednotek
	tex_person = imageloader_load("data/catarcher.png", 4, GL_RGBA);
	glBindTexture(GL_TEXTURE_2D, tex_person);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
}

//pridani jednoho objektu
object& object_system::add_one()
{
	objects.push_back(object());
	return objects.back();
}

//update vsech objektu v case
void object_system::update(float time, world& w)
{
	list<list<object>::iterator> todel;
	for (list<object>::iterator i = objects.begin();
		i != objects.end();++i) {
		
		i->update(time, w);
		if (i->deletable()) todel.push_back(i);
	}
	while (!todel.empty()) {
		objects.erase(todel.front());
		todel.pop_front();
	}
}

//nakresleni vsech objektu v case
void object_system::draw(world &w)
{
	for (list<object>::iterator i = objects.begin();i != objects.end();++i)
		i->draw(tex_tree1, tex_tree2, tex_tree3, tex_snowy_tree2,
			tex_snowy_tree3, tex_person, w);
}

//zajistuje kolize a ztratu hp objektu
bool object_system::try_to_damage_object(vect missile_pos, float dmg,
                                         float fire)
{

	for (list<object>::iterator i = objects.begin();i != objects.end();++i)
		if (i->collides(missile_pos)) {
			i->accept_damage(dmg, fire);
			return true;
		}
	return false;
}

void object_system::finish()
{
	objects.clear();
	imageloader_free(tex_tree1);
	imageloader_free(tex_tree2);
	imageloader_free(tex_tree3);
	imageloader_free(tex_snowy_tree2);
	imageloader_free(tex_snowy_tree3);
	imageloader_free(tex_person);
}

//funkce pro zajisteni smazani nekterych objektu
void object_system::delete_object(int x)
{
	int c = 0;
	for (list<object>::iterator i = objects.begin();i != objects.end();++i) {
		if (c == x)
			if (i->type == object_person) {
				i->hp = 0;
				break;
			}
		c++;
	}
}

/* =========================================================== */

void object::update(float time, world& w)
{
	float border;

	if (w.weather == rainy) burning *= 0.75;
	if (w.weather == snowy) burning *= 0.85;

	burning -= time;
	reload += time;
	if (burning < 0) burning = 0;
	else hp -= time;

	while (reload > 0) {
		switch (type) {
			//jednotky
		case object_person:
			//pohyb jednotek
			pos += spd * time;
			pos.z = w.hm.get_height(pos.x, pos.y);
			//hranice chuze pro jednotky
			border = 10 * size;
			if (pos.x - start_pos.x >= border) {
				pos.x = start_pos.x + border;
				spd.x *= -1;
			}
			if (pos.x - start_pos.x <= -border) {
				pos.x = start_pos.x - border;
				spd.x *= -1;
			}
			if (pos.y - start_pos.y >= border) {
				pos.y = start_pos.y + border;
				spd.y *= -1;
			}
			if (pos.y - start_pos.y <= -border) {
				pos.y = start_pos.y - border;
				spd.y *= -1;
			}

			//obrana jednotek - strelba
			if (w.dr.in_range(pos) && (reload > 0)) {
				missile& m = w.ms.add_one();
				m.pos = pos;
				//vypocet pozice draka v okamziku,
				//kdy k nemu doletne strela jednotky
				vect target = w.dr.pos + w.dr.spd
				              * ((w.dr.pos - pos).length())
				              / (10 + 5 * w.difficulty);
				m.spd = (target - pos)
				        | (10 + 5 * w.difficulty);

				m.type = missile_human_shot;
				m.power = 1;
				reload -= 15 / ((w.difficulty + 1) * 2) * FRAND;
				w.snd.play_arrow(w.dr, m);
			}

			if (burning > 0) {
				//partikly pro horeni poskozenych jednotek
				particle& p = w.ps.add_one();
				p.pos = pos + vect(DFRAND, DFRAND, 0);
				p.spd = vect(DFRAND * 0.2, DFRAND * 0.2,
				             2 + FRAND);
				p.type = part_small_burning;
				p.life = 1;
				p.r = 1;
				p.g = FRAND / 2;
				p.b = 0.01;
			}
			break;

			//stromy
		case object_tree1:
		case object_tree2:
		case object_tree3:
			if (burning > 0) {
				//partikly pro horeni poskozenych stromu
				particle& p = w.ps.add_one();
				p.pos = pos + vect(DFRAND, DFRAND, 0);
				if (type == object_tree1)
					p.pos = pos + vect(2 * DFRAND,
					2 * DFRAND, DFRAND * size);
				p.spd = vect(DFRAND * 0.2, DFRAND * 0.2,
				        2 + FRAND);
				p.type = part_burning;
				if (type == object_tree3)
					p.type = part_small_burning;
				p.life = 1;
				p.r = 1;
				p.g = FRAND / 2;
				p.b = 0.01;
			}
			break;
		}
		reload -= 0.02;
	}
}

void object::draw(GLuint tex_tree1, GLuint tex_tree2, GLuint tex_tree3,
	GLuint tex_snowy_tree2, GLuint tex_snowy_tree3, GLuint tex_person,
	world &w)
{

	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.3);
	glEnable(GL_TEXTURE_2D);

	glPushMatrix();
	glTranslatef(pos.x, pos.y, pos.z);
	switch (type) {
		//jednotky
	case object_person:
		glBindTexture(GL_TEXTURE_2D, tex_person);

		glBegin(GL_QUADS);
		//prvni stena
		glNormal3f(0, 1, 0);
		glTexCoord2f(1, 1);
		glVertex3f(-size, 0, 0);
		glTexCoord2f(0, 1);
		glVertex3f(size, 0, 0);
		glTexCoord2f(0, 0);
		glVertex3f(size, 0, 2*size);
		glTexCoord2f(1, 0);
		glVertex3f(-size, 0, 2*size);

		glNormal3f(0, -1, 0);
		glTexCoord2f(1, 1);
		glVertex3f(-size, 0, 0);
		glTexCoord2f(1, 0);
		glVertex3f(-size, 0, 2*size);
		glTexCoord2f(0, 0);
		glVertex3f(size, 0, 2*size);
		glTexCoord2f(0, 1);
		glVertex3f(size, 0, 0);

		//druha stena - predni cast
		glNormal3f(1, 0, 0);
		glTexCoord2f(1, 1);
		glVertex3f(0, -size, 0);
		glTexCoord2f(0.5, 1);
		glVertex3f(0, 0, 0);
		glTexCoord2f(0.5, 0);
		glVertex3f(0, 0, 2*size);
		glTexCoord2f(1, 0);
		glVertex3f(0, -size, 2*size);

		glNormal3f(1, 0, 0);
		glTexCoord2f(0.5, 1);
		glVertex3f(0, 0, 0);
		glTexCoord2f(1, 1);
		glVertex3f(0, size, 0);
		glTexCoord2f(1, 0);
		glVertex3f(0, size, 2*size);
		glTexCoord2f(0.5, 0);
		glVertex3f(0, 0, 2*size);

		//druha stena - zadni cast
		glNormal3f(-1, 0, 0);
		glTexCoord2f(0, 1);
		glVertex3f(0, -size, 0);
		glTexCoord2f(0, 0);
		glVertex3f(0, -size, 2*size);
		glTexCoord2f(0.5, 0);
		glVertex3f(0, 0, 2*size);
		glTexCoord2f(0.5, 1);
		glVertex3f(0, 0, 0);

		glNormal3f(-1, 0, 0);
		glTexCoord2f(0.5, 1);
		glVertex3f(0, 0, 0);
		glTexCoord2f(0.5, 0);
		glVertex3f(0, 0, 2*size);
		glTexCoord2f(0, 0);
		glVertex3f(0, size, 2*size);
		glTexCoord2f(0, 1);
		glVertex3f(0, size, 0);
		glEnd();

/*
		glColor3f (1, 1, 1);
		//telo
		glBegin (GL_LINE_STRIP);
		glVertex3f (-size / 2, 0, 0);
		glVertex3f (0, 0, size / 2);
		glVertex3f (size / 2, 0, 0);
		glVertex3f (0, 0, size / 2);
		glVertex3f (0, 0, size);
		glVertex3f (size / 2, 0, 3*size / 4);
		glVertex3f (0, 0, size);
		glVertex3f (-size / 2, 0, 3*size / 4);
		glVertex3f (0, 0, size);
		glVertex3f (0, 0, 3*size / 2);
		glEnd();

		//hlava
		glColor3f (1, 0, 0);
		glBegin (GL_TRIANGLE_FAN);
		glVertex3f (0, 0, 3*size / 2);
		glVertex3f (0, -size / 4, size + 3*size / 4);
		glVertex3f (-size / 4, 0, size + 3*size / 4);
		glVertex3f (0, size / 4, size + 3*size / 4);
		glVertex3f (size / 4, 0, size + 3*size / 4);
		glVertex3f (0, -size / 4, size + 3*size / 4);
		glEnd();
		glColor3f (1, 1, 0);
		glBegin (GL_TRIANGLE_FAN);
		glNormal3f (0, 0, 1);
		glVertex3f (0, 0, 2*size);
		glVertex3f (0, -size / 4, size + 3*size / 4);
		glVertex3f (size / 4, 0, size + 3*size / 4);
		glVertex3f (0, size / 4, size + 3*size / 4);
		glVertex3f (-size / 4, 0, size + 3*size / 4);
		glVertex3f (0, -size / 4, size + 3*size / 4);
		glEnd();
		break;
*/
		break;
	case object_tree1:
	case object_tree2:
	case object_tree3:
		if (type == object_tree1) {
			if (w.weather != snowy) 
				glBindTexture(GL_TEXTURE_2D, tex_tree1);
			else break;
		}
		if (type == object_tree2) {
			if (w.weather != snowy)
				glBindTexture(GL_TEXTURE_2D, tex_tree2);
			else 
				glBindTexture(GL_TEXTURE_2D, tex_snowy_tree2);
		}
		if (type == object_tree3) {
			if (w.weather != snowy) 
				glBindTexture(GL_TEXTURE_2D, tex_tree3);
			else 
				glBindTexture(GL_TEXTURE_2D, tex_snowy_tree3);
		}

		glBegin(GL_QUADS);
		//prvni stena
		glNormal3f(0, 1, 0);
		glTexCoord2f(1, 1);
		glVertex3f(-size, 0, 0);
		glTexCoord2f(0, 1);
		glVertex3f(size, 0, 0);
		glTexCoord2f(0, 0);
		glVertex3f(size, 0, 2*size);
		glTexCoord2f(1, 0);
		glVertex3f(-size, 0, 2*size);

		glNormal3f(0, -1, 0);
		glTexCoord2f(1, 1);
		glVertex3f(-size, 0, 0);
		glTexCoord2f(1, 0);
		glVertex3f(-size, 0, 2*size);
		glTexCoord2f(0, 0);
		glVertex3f(size, 0, 2*size);
		glTexCoord2f(0, 1);
		glVertex3f(size, 0, 0);

		//druha stena
		glNormal3f(1, 0, 0);
		glTexCoord2f(1, 1);
		glVertex3f(0, -size, 0);
		glTexCoord2f(0, 1);
		glVertex3f(0, size, 0);
		glTexCoord2f(0, 0);
		glVertex3f(0, size, 2*size);
		glTexCoord2f(1, 0);
		glVertex3f(0, -size, 2*size);

		glNormal3f(-1, 0, 0);
		glTexCoord2f(1, 1);
		glVertex3f(0, -size, 0);
		glTexCoord2f(1, 0);
		glVertex3f(0, -size, 2*size);
		glTexCoord2f(0, 0);
		glVertex3f(0, size, 2*size);
		glTexCoord2f(0, 1);
		glVertex3f(0, size, 0);
		glEnd();

		break;
	}
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	glEnable(GL_ALPHA_TEST);
}

//prijeti poskozeni a horeni
void object::accept_damage(float dmg, float fire)
{
	hp -= dmg;
	burning += fire;
}

//kolize objektu se strelami
bool object::collides(vect missile_pos)
{
	if (type == object_person) {
		if ((pos - missile_pos).length() < size) return true;
	} else if (type == object_tree1 || type == object_tree2) {
		if ((pos - missile_pos).length() < 1.5*size) return true;
	} else if (type == object_tree3) {
		if ((pos - missile_pos).length() < size) return true;
	}
	return false;
}

//funkce pro overeni smazatelnosti strely
bool object::deletable()
{
	if (hp <= 0) return true;
	return false;
}

