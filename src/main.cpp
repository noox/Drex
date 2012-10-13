
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <math.h>

#include <iostream>
using namespace std;

#include "game.h"

static SDL_Surface *surface;

bool init(){
	if(SDL_Init(SDL_INIT_VIDEO) < 0){
		cout << "SDL_Init failed: " << SDL_GetError() << endl;
		return false;
	}
	
	//ziskacni informaci o grafickych moznostech
	const SDL_VideoInfo *videoinfo;
	videoinfo = SDL_GetVideoInfo();
	if(!videoinfo) {
		cout << "SDL_GetVideoInfo failed: " << SDL_GetError() << endl;
		return false;
	}
	
	//vlastnosti videa
	int vidflags = SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_HWPALETTE;
	if(videoinfo->hw_available) vidflags |= SDL_HWSURFACE;
	else vidflags |= SDL_SWSURFACE;
	if(videoinfo->blit_hw) vidflags |= SDL_HWACCEL;

	SDL_GL_SetAttribute (SDL_GL_DOUBLEBUFFER,1);
	SDL_GL_SetAttribute (SDL_GL_BUFFER_SIZE,24);
	SDL_GL_SetAttribute (SDL_GL_DEPTH_SIZE,16);
	
	//povrch na kresleni (okno)
	surface = SDL_SetVideoMode(800,600,24,vidflags);
	if(!surface){
		cout << "SDL_SetVideoMode failed: " << SDL_GetError() << endl;
		return false;
	}
	
	//titulek okna
	SDL_WM_SetCaption("drex",NULL);

	glViewport(0,0,800,600);
	
	//chyti a schova mys
	SDL_WM_GrabInput(SDL_GRAB_ON);
	SDL_ShowCursor(SDL_DISABLE);

	return true;
}

void finish(){
	SDL_Quit();
}

static long int lasttime;

//zmeri casovy usek v sekundach od minuleho volani timediff
float timediff(){
	Uint32 newtime = SDL_GetTicks();
	float diff = (newtime-lasttime) / 1000.0;
	lasttime=newtime;
	return diff;
}

void sleep(float t){
	SDL_Delay((Uint32)(1000*t));
}

static bool space_down = false, tab_down = false, esc_down = false,
	left_mouse_down = false, right_mouse_down = false;
game global_game;

bool update(){
	SDL_Event event;
	while(SDL_PollEvent(&event)){
		switch(event.type){
			case SDL_QUIT: return false;
			case SDL_KEYUP: 
				if(event.key.keysym.sym==SDLK_SPACE)
					space_down=false;
				if(event.key.keysym.sym==SDLK_ESCAPE)
					esc_down=false;
				if(event.key.keysym.sym==SDLK_TAB)
					tab_down=false;
				break;
			case SDL_KEYDOWN: 
				if(event.key.keysym.sym==SDLK_SPACE)
					space_down=true;
				if(event.key.keysym.sym==SDLK_ESCAPE)
					esc_down=true;
				if(event.key.keysym.sym==SDLK_TAB)
					tab_down=true;
				if(event.key.keysym.sym==SDLK_F12)
					return false;
				break;
			case SDL_MOUSEBUTTONUP: 
				if(event.button.button==SDL_BUTTON_LEFT)
					left_mouse_down=false;
				if(event.button.button==SDL_BUTTON_RIGHT)
					right_mouse_down=false;
				break;
			case SDL_MOUSEBUTTONDOWN: 
				if(event.button.button==SDL_BUTTON_LEFT)
					left_mouse_down=true;
				if(event.button.button==SDL_BUTTON_RIGHT)
					right_mouse_down=true;
				//cout << "Mouse button " << (int)event.button.button << " pressed at " << event.button.x << ", " << event.button.y << endl;
             			break;
			default: break;
		}
	}

	int mouse_x, mouse_y;
	SDL_GetRelativeMouseState (&mouse_x, &mouse_y);
	//cout << mouse_x << ", " << mouse_y << endl;

	float td = timediff();
	float min_td = global_game.get_min_timediff();
	
	//kdyz chce hra omezovat fps a kdyz je co omezovat
	if(min_td>0 && td<min_td){
		sleep(min_td-td);
		td += timediff();
	}

	bool term = global_game.update(td,space_down,tab_down,esc_down,left_mouse_down,right_mouse_down,mouse_x,mouse_y);
	global_game.render();
	
	//dalsi snimek
	SDL_GL_SwapBuffers();
	
	return term;
}

#ifndef __WIN32__
int main(int argc, char **argv){
#else
#include <windows.h>
int WinMain(HINSTANCE hi, HINSTANCE hpi, LPSTR lpcmdline, int nCmdShow) {
#endif
	if(!init()) return 1;
	global_game.init();

	//reset casovace
	timediff();
	
	while(update());
	
	global_game.finish();
	finish();
	
	return 0;
}

