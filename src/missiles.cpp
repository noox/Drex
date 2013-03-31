
#include <GL/gl.h>
#include <math.h>

#include "missiles.h"
#include "frand.h"
#include "world.h"
#include "imageloader.h"

void missile_system::init()
{
	missiles.clear();

	tex_fireball = imageloader_load("data/fireball.png", 4, GL_RGBA);
	glBindTexture(GL_TEXTURE_2D, tex_fireball);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
}

//pridani jedne strely
missile& missile_system::add_one()
{
	missiles.push_back(missile());
	return missiles.back();
}

//update vsech strel a smazani nepotrebnych
void missile_system::update(float time, world& w)
{
	list<list<missile>::iterator> todel;
	for (list<missile>::iterator i = missiles.begin();i != missiles.end();
	        ++i) {

		i->update(time, w);
		if (i->deletable) todel.push_back(i);
	}
	while (!todel.empty()) {
		missiles.erase(todel.front());
		todel.pop_front();
	}
}

void missile_system::draw(world &w)
{
	for (list<missile>::iterator i = missiles.begin();i != missiles.end();
	        ++i) i->draw(w, tex_fireball);
}

void missile_system::finish()
{
	missiles.clear();
}

/* =========================================================== */

void missile::update(float time, world& w)
{
	pos += spd * time;
	age += time;
	reload += time;

	while (reload > 0) {
		//pokud strela existuje moc dlouho, preda se ke smazani
		if (age > 3) deletable = true;

		switch (type) {

			//zakladni draci utok
		case missile_dragon_fire:
			//pokud strela zasahla cil, preda se ke smazani
			if (w.es.try_to_damage_enemy(pos, power, fire)
			        || w.ob.try_to_damage_object(pos, power, fire))

				deletable = true;

			//pridani particlu do systemu
			{
				particle& p = w.ps.add_one();
				p.pos = pos;
				p.spd = vect(DFRAND, DFRAND, DFRAND);
				p.type = part_fire;
				p.life = 0.4;
				p.r = 1;
				p.g = FRAND / 2;
				p.b = 0.01;
			}
			break;

			//pokrocily draci utok
		case missile_dragon_ball:
			//pokud strela zasahla cil, preda se ke smazani
			if (w.es.try_to_damage_enemy(pos, power, fire)
			        || w.ob.try_to_damage_object(pos, power, fire))

				deletable = true;

			//pridani particlu do systemu
			{
				particle& p = w.ps.add_one();
				p.pos = pos;
				p.spd = vect(DFRAND, DFRAND, DFRAND);
				p.type = part_fireball;
				p.life = 0.4;
				p.r = 1;
				p.g = FRAND / 2;
				p.b = 0.01;
			}
			break;

			//utok nepratel
		case missile_human_shot:
			//pokud strela zasahla draka, preda se ke smazani
			if (w.dr.try_to_damage_dragon(pos, power))
				deletable = true;

			//pridani particlu do systemu
			{
				particle& p = w.ps.add_one();
				p.pos = pos;
				p.spd = vect(DFRAND, DFRAND, DFRAND);
				p.type = part_fire;
				p.life = 0.4;
				p.r = 1;
				p.g = 0.01;
				p.b = 0.01;
			}
			break;
		}
		reload -= 0.01;
	}
}

void missile::draw(world &w, GLuint tex_fireball)
{
	//priprava matice pro billboarding
	float part_face[16];
	for (int i = 0;i < 16;++i) part_face[i] = 0;
	vect temp = w.cam.ori.vecx();
	part_face[0] = temp.x;
	part_face[1] = temp.y;
	part_face[2] = temp.z;
	part_face[3] = 0;
	temp = w.cam.ori.vecy();
	part_face[4] = temp.x;
	part_face[5] = temp.y;
	part_face[6] = temp.z;
	part_face[7] = 0;
	temp = w.cam.ori.vecz();
	part_face[8] = temp.x;
	part_face[9] = temp.y;
	part_face[10] = temp.z;
	part_face[11] = 0;
	part_face[12] = 0;
	part_face[13] = 0;
	part_face[14] = 0;
	part_face[15] = 1;

	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.3);

	if (type == missile_dragon_ball) {
		glPushMatrix();
		glTranslatef(pos.x, pos.y, pos.z);

		glBindTexture(GL_TEXTURE_2D, tex_fireball);
		glEnable(GL_TEXTURE_2D);

		glMultMatrixf(part_face);
		glBegin(GL_POLYGON);
		float rad, xcos, xsin;
		for (int i = 0;i < 360;++i) {
			rad = i * M_PI / 180;
			xcos = cos(rad);
			xsin = sin(rad);

			glTexCoord2f(xcos * 0.5 + 0.5, xsin * 0.5 + 0.5);
			glVertex2f(xcos, xsin);
		}
		glEnd();

		glDisable(GL_TEXTURE_2D);

		glPopMatrix();
	}
	glDisable(GL_ALPHA_TEST);
}

