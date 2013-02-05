
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>

using namespace std;

#include "game.h"
#include "frand.h"
#include "imageloader.h"
#include "navigation.h"
#include "world.h"

void world::init(){
	dr.init();
	dr.set(vect(10,10,10),quat(0.7,0.7,0,0));
	cam.set(vect(0,0,0),quat(1,0,0,0));
	hm.init();
	hm.load("data/hm3.png","data/color3.png");
	es.init();
	ps.init();
	ms.init();

	tab_hit=0;

	glShadeModel(GL_SMOOTH);
	glFrontFace(GL_CCW);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
	
	glEnable(GL_DEPTH_TEST);
	
	//pro nerenderovani veci v pozadi
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	//inicialni nastaveni pro mlhu
	glHint(GL_FOG_HINT,GL_NICEST);
	f.set_color(0.4,0.6,0.9);
	f.set_distance(50,200);

	float hm_x,hm_y;
	hm.get_sizes(hm_x,hm_y);
	for(int i=0;i<8;++i) {
		enemy& p = es.add_one();
		p.spd.x=0;
		p.spd.y=0;
		p.spd.z=0;
		p.pos.x=(0.13+FRAND*0.02)*hm_x;
		p.pos.y=(0.13+FRAND*0.02)*hm_y;
		p.pos.z=hm.get_height(p.pos.x,p.pos.y);
		p.size_x=1+FRAND;
		p.size_y=1+FRAND;
		p.size_z=1+FRAND;
		p.roof_size=2*FRAND;
		p.rot=360*FRAND;
		p.type=enemy_house;
		p.hp=100;
	}
	for(int i=0;i<20;++i) {
		enemy& p = es.add_one();
		p.spd.x=0;
		p.spd.y=0;
		p.spd.z=0;
		p.pos.x=(0.3+FRAND*0.03)*hm_x;
		p.pos.y=(0.3+FRAND*0.03)*hm_y;
		p.pos.z=hm.get_height(p.pos.x,p.pos.y);
		p.size_x=1+FRAND;
		p.size_y=1+FRAND;
		p.size_z=1+FRAND;
		p.roof_size=2*FRAND;
		p.rot=360*FRAND;
		p.type=enemy_house;
		p.hp=100;
	}
	for(int i=0;i<5;++i) {
		enemy& p = es.add_one();
		p.spd.x=0;
		p.spd.y=0;
		p.spd.z=0;
		p.pos.x=(0.13+FRAND*0.02)*hm_x;
		p.pos.y=(0.3+FRAND*0.02)*hm_y;
		p.pos.z=hm.get_height(p.pos.x,p.pos.y);
		p.size_x=1+FRAND;
		p.size_y=1+FRAND;
		p.size_z=1+FRAND;
		p.roof_size=2*FRAND;
		p.rot=360*FRAND;
		p.type=enemy_house;
		p.hp=100;
	}
}

void world::finish(){
	hm.finish();
	dr.finish();
	es.finish();
	ps.finish();
	ms.finish();
}

bool world::update(float timediff,bool space_down,bool tab_down,bool esc_down,bool left_mouse_down,bool right_mouse_down,int mouse_x,int mouse_y){
	dr.update(mouse_x,mouse_y,left_mouse_down,right_mouse_down,space_down,timediff,*this);
	es.update(timediff,*this);
	ps.update(timediff);
	ms.update(timediff,*this);
	cam.follow_ori(dr.ori,0.01,timediff);
	cam.follow_pos(dr.camera_pos(),0.1,timediff);
	cam.collide_with_heightmap(hm);

	int tab_just_pressed=0;
	//proti sekvencim stisknutych tlacitek
	if (tab_down) {
		if (!tab_hit)
			tab_just_pressed=tab_hit=1;
	} else tab_hit=0;
	//pro navigaci po mape
	if(tab_just_pressed) make_navigation(timediff,*this);
	
	//pro ukonceni hry
	if(es.all_enemies_dead()) return false;
	return true;
}

void world::render(){
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90,1.33333,0.1,1000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	cam.set_gl();
	skyb.draw(cam.pos);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
	{
	float light_direction[]={0.4082,0.4082,0.8165,0};
	glLightfv(GL_LIGHT0, GL_POSITION, light_direction);
	}
	f.turn_on();
	dr.draw();
	hm.draw();
	es.draw();
	ms.draw();
	f.turn_off();

	glDisable(GL_LIGHTING);
	ps.draw(*this);


	glDepthMask(GL_FALSE);
	glDisable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0,800,600,0,-1,1);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glEnable(GL_BLEND);
	glColor4f(0.5,0.5,0.5,0.2);
	glBegin(GL_QUADS);
	glVertex2f(50,50);
	glVertex2f(50,100);
	glVertex2f(100,100);
	glVertex2f(100,50);
	glEnd();
	glDisable(GL_BLEND);

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
}

