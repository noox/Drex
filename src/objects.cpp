
#include <iostream>
using namespace std;

#include <GL/gl.h>

#include "objects.h"
#include "world.h"
#include "frand.h"

void object_system::init() {
	objects.clear();
}

//pridani jednoho objektu
object& object_system::add_one() {
	objects.push_back (object() );
	return objects.back();
}

//update vsech objektu v case
void object_system::update (float time, world& w) {
	list<list<object>::iterator> todel;
	for (list<object>::iterator i = objects.begin();i != objects.end();++i) {
		i->update (time, w);
		if (i->deletable() ) todel.push_back (i);
	}
	while (!todel.empty() ) {
		objects.erase (todel.front() );
		todel.pop_front();
	}
}

//nakresleni vsech objektu v case
void object_system::draw() {
	for (list<object>::iterator i = objects.begin();i != objects.end();++i)
		i->draw();
}

//zajistuje kolize a ztratu hp objektu
bool object_system::try_to_damage_object (vect missile_pos, float dmg, float fire) {
	for (list<object>::iterator i = objects.begin();i != objects.end();++i)
		if (i->collides (missile_pos) ) {
			i->accept_damage (dmg, fire);
			return true;
		}
	return false;
}

void object_system::finish() {
	objects.clear();
}

//funkce pro zjisteni zbytku objektu
bool object_system::all_objects_dead() {
	if (objects.empty() ) return true;
	return false;
}
/* =========================================================== */

void object::update (float time, world& w) {
	float border;
	switch (type) {
		//lide
	case object_person:
		burning -= time;
		if (burning < 0) burning = 0;
		else hp -= time * 5;

		//pohyb lidi
		pos += spd * time;
		pos.z = w.hm.get_height (pos.x, pos.y);
		//hranice chuze pro lidi
		border = 10 * size_p;
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

		reload += time;
		if (w.dr.in_range (pos) && (reload > 0) ) {
			missile& m = w.ms.add_one();
			m.pos = pos;
			vect target = w.dr.pos + w.dr.spd * ( (w.dr.pos - pos).length() ) / 10;
			m.spd = (target - pos) | 10;
			m.type = missile_human_shot;
			m.power = 1;
			reload -= 15*FRAND/((w.difficulty+1)+0.5*w.difficulty*w.difficulty);
		}

		if (burning > 0) {
			//partikly pro horeni poskozenych nepratel
			particle& p = w.ps.add_one();
			p.pos = pos + vect (0, 0, DFRAND * size_p);
			p.spd = vect (DFRAND * 0.2, DFRAND * 0.2, 2 + FRAND);
			p.type = part_fire;
			p.life = 1;
			p.r = 1;
			p.g = FRAND / 2;
			p.b = 0.01;
			//TODO particle jednou za cas
		}

		if (deletable() ) {
			//vybuch z partiklu, pokud nepritel ztrati hp
			for (int i = 0;i < 100;++i) {
				{
					particle& p = w.ps.add_one();
					p.pos = pos;
					p.spd = vect (DFRAND, DFRAND, DFRAND).normal() * 5;
					p.type = part_fire;
					p.life = 1;
					p.r = 1;
					p.g = 0;
					p.b = 0;
				}
				//TODO particle jednou za cas
				{
					particle& p = w.ps.add_one();
					p.pos = pos + vect (DFRAND, DFRAND, DFRAND);
					p.spd = vect (DFRAND, DFRAND, DFRAND).normal() * 0.5;
					p.type = part_smoke;
					p.life = 3;
					p.r = 1;
					p.g = 0;
					p.b = 0;
				}
			}
		}
		break;

		//stromy
	case object_tree:
		burning -= time;
		if (burning < 0) burning = 0;
		else hp -= time * 5;

		if (burning > 0) {
			//partikly pro horeni poskozenych stromu
			particle& p = w.ps.add_one();
			p.pos = pos + vect (0, 0, DFRAND * size_tr);
			p.spd = vect (DFRAND * 0.2, DFRAND * 0.2, 2 + FRAND);
			p.type = part_fire;
			p.life = 1;
			p.r = 1;
			p.g = FRAND / 2;
			p.b = 0.01;
			//TODO particle jednou za cas
		}
		break;
	}
}

void object::draw() {
	float temp;
	glPushMatrix();
	glTranslatef (pos.x, pos.y, pos.z);
	switch (type) {
		//lide
	case object_person:
		glColor3f (1, 1, 1);
		//telo
		glBegin (GL_LINE_STRIP);
		glVertex3f (-size_p / 2, 0, 0);
		glVertex3f (0, 0, size_p / 2);
		glVertex3f (size_p / 2, 0, 0);
		glVertex3f (0, 0, size_p / 2);
		glVertex3f (0, 0, size_p);
		glVertex3f (size_p / 2, 0, 3*size_p / 4);
		glVertex3f (0, 0, size_p);
		glVertex3f (-size_p / 2, 0, 3*size_p / 4);
		glVertex3f (0, 0, size_p);
		glVertex3f (0, 0, 3*size_p / 2);
		glEnd();

		//hlava
		glColor3f (1, 0, 0);
		glBegin (GL_TRIANGLE_FAN);
		glVertex3f (0, 0, 3*size_p / 2);
		glVertex3f (0, -size_p / 4, size_p + 3*size_p / 4);
		glVertex3f (-size_p / 4, 0, size_p + 3*size_p / 4);
		glVertex3f (0, size_p / 4, size_p + 3*size_p / 4);
		glVertex3f (size_p / 4, 0, size_p + 3*size_p / 4);
		glVertex3f (0, -size_p / 4, size_p + 3*size_p / 4);
		glEnd();
		glColor3f (1, 1, 0);
		glBegin (GL_TRIANGLE_FAN);
		glNormal3f (0, 0, 1);
		glVertex3f (0, 0, 2*size_p);
		glVertex3f (0, -size_p / 4, size_p + 3*size_p / 4);
		glVertex3f (size_p / 4, 0, size_p + 3*size_p / 4);
		glVertex3f (0, size_p / 4, size_p + 3*size_p / 4);
		glVertex3f (-size_p / 4, 0, size_p + 3*size_p / 4);
		glVertex3f (0, -size_p / 4, size_p + 3*size_p / 4);
		glEnd();
		break;
		//stromy
	case object_tree:
		//kmen
		glColor3f (1, 0.5, 0);
		glBegin (GL_LINES);
		glVertex3f (0, 0, 0);
		glVertex3f (0, 0, size_tr / 2);
		glEnd();
		//koruna
		glColor3f (0.5, 1, 0.5);
		glBegin (GL_TRIANGLE_FAN);
		glVertex3f (0, 0, size_tr / 2);
		glVertex3f (0, -size_tr / 2, size_tr + size_tr / 4);
		glVertex3f (-size_tr / 2, 0, size_tr + size_tr / 4);
		glVertex3f (0, size_tr / 2, size_tr + size_tr / 4);
		glVertex3f (size_tr / 2, 0, size_tr + size_tr / 4);
		glVertex3f (0, -size_tr / 2, size_tr + size_tr / 4);
		glEnd();
		glColor3f (0.2, 1, 0);
		glBegin (GL_TRIANGLE_FAN);
		glNormal3f (0, 0, 1);
		glVertex3f (0, 0, 2*size_tr);
		glVertex3f (0, -size_tr / 2, size_tr + size_tr / 4);
		glVertex3f (size_tr / 2, 0, size_tr + size_tr / 4);
		glVertex3f (0, size_tr / 2, size_tr + size_tr / 4);
		glVertex3f (-size_tr / 2, 0, size_tr + size_tr / 4);
		glVertex3f (0, -size_tr / 2, size_tr + size_tr / 4);
		glEnd();
		break;
	}
	glPopMatrix();
}

//prijeti poskozeni a horeni
void object::accept_damage (float dmg, float fire) {
	hp -= dmg;
	burning += fire;
}

//kolize objektu se strelami
bool object::collides (vect missile_pos) {
	if (type == object_person || type == object_shooting_person) {
		if ( (pos - missile_pos).length() < size_p) return true;
	} else if (type == object_tree) {
		if ( (pos - missile_pos).length() < 1.5*size_tr) return true;
	}
	return false;
}

//funkce pro overeni smazatelnosti strely
bool object::deletable() {
	if (hp < 0) return true;
	return false;
}


