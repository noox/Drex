
#include <GL/gl.h>
#include <iostream>

using namespace std;

#include "enemy.h"
#include "world.h"
#include "frand.h"
#include "imageloader.h"

void enemy_system::init()
{
	enemies.clear();

	tex_wall = imageloader_load("data/wall.png", 3, GL_RGB);
	glBindTexture(GL_TEXTURE_2D, tex_wall);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	tex_red_roof = imageloader_load("data/red_roof.png", 3, GL_RGB);
	glBindTexture(GL_TEXTURE_2D, tex_red_roof);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	tex_black_roof = imageloader_load("data/black_roof.png", 3, GL_RGB);
	glBindTexture(GL_TEXTURE_2D, tex_black_roof);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	tex_snowy_roof = imageloader_load("data/snowy_roof.png", 3, GL_RGB);
	glBindTexture(GL_TEXTURE_2D, tex_snowy_roof);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	tex_burning_roof = imageloader_load("data/burning_roof.png", 3,
	                                    GL_RGB);
	glBindTexture(GL_TEXTURE_2D, tex_burning_roof);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
}

//pridani jednoho nepritele
enemy& enemy_system::add_one()
{
	enemies.push_back(enemy());
	return enemies.back();
}

//update vsech nepratel v case
void enemy_system::update(float time, world& w)
{
	int c = 0;
	list<list<enemy>::iterator> todel;
	for (list<enemy>::iterator i = enemies.begin();i != enemies.end();++i) {
		i->update(time, w);
		if (i->deletable()) {
			todel.push_back(i);
			w.remove_object(c);
		}
		c++;
	}
	while (!todel.empty()) {
		enemies.erase(todel.front());
		todel.pop_front();
	}
}

//nakresleni vsech nepratel v case
void enemy_system::draw(world& w)
{
	for (list<enemy>::iterator i = enemies.begin();i != enemies.end();++i)
		i->draw(tex_wall, tex_red_roof, tex_black_roof, tex_snowy_roof,
		        tex_burning_roof, w);
}

//zajistuje kolize a ztratu hp nepratel
bool enemy_system::try_to_damage_enemy(vect missile_pos, float dmg,
                                       float fire)
{

	for (list<enemy>::iterator i = enemies.begin();i != enemies.end();++i)
		if (i->collides(missile_pos)) {
			i->accept_damage(dmg, fire);
			return true;
		}
	return false;
}

void enemy_system::finish()
{
	enemies.clear();
	imageloader_free(tex_wall);
	imageloader_free(tex_red_roof);
	imageloader_free(tex_black_roof);
	imageloader_free(tex_snowy_roof);
	imageloader_free(tex_burning_roof);
}

//funkce pro zjisteni zbytku nepratel - pro konec hry
bool enemy_system::all_enemies_dead()
{
	if (enemies.empty()) return true;
	return false;
}

//pozice nejakeho nepritele - pro navigaci
vect enemy_system::one_enemy()
{
	return enemies.front().pos;
}

/* =========================================================== */

void enemy::update(float time, world& w)
{
	//zkraceni horeni objektu za deste a snehu
	if (w.weather == rainy) burning *= 0.75;
	if (w.weather == snowy) burning *= 0.85;

	burning -= time;
	reload += time;
	if (burning < 0) burning = 0;
	else hp -= time;

	while (reload > 0) {
		if (burning > 0)  {
			//partikly pro horeni poskozenych domu
			particle& p = w.ps.add_one();
			p.pos = pos + vect(DFRAND * size_x, DFRAND * size_y,
			                   size_z + DFRAND * roof_size / 5);
			p.spd = vect(DFRAND * 0.2, DFRAND * 0.2, 2 + FRAND);
			p.type = part_burning;
			p.life = 1;
			p.r = 1;
			p.g = FRAND / 2;
			p.b = 0.01;

			if (!noise) {
				w.snd.play_burn(w.dr, pos);
				noise = true;
			}
		} else if (noise) noise = false;

		/*	if (deletable() ) {
				//vybuch z partiklu, pokud dum ztrati hp
				for (int i = 0;i < 100;++i) {
					{
						particle& p = w.ps.add_one();
						p.pos = pos;
						p.spd = vect (DFRAND, DFRAND, 
							DFRAND).normal() * 5;
						p.type = part_burning;
						p.life = 1;
						p.r = 1;
						p.g = FRAND / 2;
						p.b = 0.01;
					}
					{
						particle& p = w.ps.add_one();
						p.pos = pos + vect (DFRAND, 
							DFRAND, DFRAND) * 3 * 
							FRAND;
						p.spd = vect (DFRAND, DFRAND, 
							DFRAND).normal() * 0.5;
						p.type = part_smoke;
						p.life = 3;
						p.r = 0.5;
						p.g = 0.5;
						p.b = 0.5;
					}
				}
			}
		*/
		reload -= 0.02;
	}
}

void enemy::draw(GLuint tex_wall, GLuint tex_red_roof, GLuint tex_black_roof,
	GLuint tex_snowy_roof, GLuint tex_burning_roof, world &w)
{
	float temp;

	glPushMatrix();
	glTranslatef(pos.x, pos.y, pos.z);
	glRotatef(rot, 0, 0, 1);
	glColor3f(1, 1, 1);

	glEnable(GL_TEXTURE_2D);

	//strecha
	if (hp < 10) {
		glBindTexture(GL_TEXTURE_2D, tex_burning_roof);
	} else {
		glBindTexture(GL_TEXTURE_2D, tex_red_roof);
		if ((int) pos.x % 2 != 0) 
			glBindTexture(GL_TEXTURE_2D, tex_black_roof);
		if (w.weather == snowy)
			glBindTexture(GL_TEXTURE_2D, tex_snowy_roof);
	}

	temp = sqrt(roof_size * roof_size + size_y * size_y);

	glBegin(GL_QUADS);
	glNormal3f(-roof_size / temp, 0, size_y / (2 * temp));
	glTexCoord2f(0, 0);
	glVertex3f(-size_x, -size_y, size_z);
	glTexCoord2f(1, 0);
	glVertex3f(size_x, -size_y, size_z);
	glTexCoord2f(1, 1);
	glVertex3f(size_x, 0, size_z + roof_size);
	glTexCoord2f(0, 1);
	glVertex3f(-size_x, 0, size_z + roof_size);

	glNormal3f(roof_size / temp, 0, size_y / (2 * temp));
	glTexCoord2f(0, 0);
	glVertex3f(-size_x, 0, size_z + roof_size);
	glTexCoord2f(1, 0);
	glVertex3f(size_x, 0, size_z + roof_size);
	glTexCoord2f(1, 1);
	glVertex3f(size_x, size_y, size_z);
	glTexCoord2f(0, 1);
	glVertex3f(-size_x, size_y, size_z);
	glEnd();

	//steny
	glBindTexture(GL_TEXTURE_2D, tex_wall);

	glBegin(GL_QUADS);
	glNormal3f(0, -1, 0);
	glTexCoord2f(0, 0);
	glVertex3f(-size_x, -size_y, 0);
	glTexCoord2f(1, 0);
	glVertex3f(size_x, -size_y, 0);
	glTexCoord2f(1, 1);
	glVertex3f(size_x, -size_y, size_z);
	glTexCoord2f(0, 1);
	glVertex3f(-size_x, -size_y, size_z);

	glNormal3f(0, 1, 0);
	glTexCoord2f(0, 0);
	glVertex3f(-size_x, size_y, 0);
	glTexCoord2f(0, 1);
	glVertex3f(-size_x, size_y, size_z);
	glTexCoord2f(1, 1);
	glVertex3f(size_x, size_y, size_z);
	glTexCoord2f(1, 0);
	glVertex3f(size_x, size_y, 0);
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(-1, 0, 0);
	glTexCoord2f(0, 0);
	glVertex3f(-size_x, -size_y, 0);
	glTexCoord2f(0, 0.5);
	glVertex3f(-size_x, -size_y, size_z);
	glTexCoord2f(0.5, 1);
	glVertex3f(-size_x, 0, size_z + roof_size);
	glTexCoord2f(1, 0.5);
	glVertex3f(-size_x, size_y, size_z);
	glTexCoord2f(0.5, 0);
	glVertex3f(-size_x, size_y, 0);
	glEnd();

	glBegin(GL_POLYGON);
	glNormal3f(1, 0, 0);
	glTexCoord2f(0, 0);
	glVertex3f(size_x, -size_y, 0);
	glTexCoord2f(1, 0);
	glVertex3f(size_x, size_y, 0);
	glTexCoord2f(1, 0.5);
	glVertex3f(size_x, size_y, size_z);
	glTexCoord2f(0.5, 1);
	glVertex3f(size_x, 0, size_z + roof_size);
	glTexCoord2f(0, 0.5);
	glVertex3f(size_x, -size_y, size_z);
	glEnd();

	glPopMatrix();
}

//prijeti poskozeni a horeni
void enemy::accept_damage(float dmg, float fire)
{
	hp -= dmg;
	burning += fire;
}

#define max(a,b) (((a)>(b))?(a):(b))
//kolize nepratel se strelami
bool enemy::collides(vect missile_pos)
{
	if ((pos - missile_pos).length() < 
		1.5 * max(max(size_x, size_y), size_z + roof_size)) return true;
	return false;
}

//funkce pro overeni smazatelnosti strely
bool enemy::deletable()
{
	if (hp <= 0) return true;
	return false;
}

