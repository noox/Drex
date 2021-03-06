
#include <SDL/SDL_image.h>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

#include "imageloader.h"
#include "game.h"

class heightmap hm;

bool imageloader_init()
{
	int flags = IMG_INIT_PNG;
	int initted = IMG_Init(flags);
	if (initted&flags != flags) return false;
	else return true;
}

void imageloader_end()
{
	IMG_Quit();
}

//loader textur
GLuint imageloader_load(const char* fn, int BPP, GLuint type)
{
	SDL_Surface *image;
	image = IMG_Load(fn);
	if (!image) return 0;
	GLuint t;
	glGenTextures(1, &t);
	glBindTexture(GL_TEXTURE_2D, t);
	glTexImage2D(GL_TEXTURE_2D, 0, BPP, image->w, image->h, 0, type,
	             GL_UNSIGNED_BYTE, image->pixels);
	SDL_FreeSurface(image);
	return t;
}

//loader mapoveho souboru (.map)
void imageloader_load_map(const char* fn, vector<int> &h, game& g, world& w, 
	int size_x, int size_y)
{
	h.resize(size_x*size_y);
	fstream f;
	f.open(fn);

	string line;

	//skip prvnich 3 radku mapoveho souboru
	for (int i = 0;i < 3;++i)
		getline(f, line, '\n');

	//vyskova mapa
	for (int i = 0;i < size_y;++i) {
		getline(f, line, '\n');
		stringstream ss(line);
		for (int j = 0;j < size_x;++j)
			ss >> h[i*size_y+j];
	}
	
	//zastavba
	float u, v;
	while (getline(f, line, '\n')) {
		stringstream ss(line);
		ss >> u >> v;
		if (u == -1 || v == -1) break;
		else w.add_enemy(hm.get_size(u), hm.get_size(v));
	}
	
	//stromy volne v nizinach a pahorkatinach
	while (getline(f, line, '\n')) {
		stringstream ss(line);
		ss >> u >> v;
		w.add_rest(hm.get_size(u), hm.get_size(v));
	}

	f.close();
}

//loader barev mapy
bool imageloader_load_color(const char* water, const char* lowland, 
	const char* upland, const char* mountain, const char* ice, 
	vector<unsigned char> &c, vector<int> h, game& g, int size_x, 
	int size_y)
{
	SDL_Surface *w, *l, *u, *m, *ic, *image;
	//priprava textur pro ruzne typy krajiny
	w = IMG_Load(water);
	l = IMG_Load(lowland);
	u = IMG_Load(upland);
	m = IMG_Load(mountain);
	ic = IMG_Load(ice);
	image = 0;
	if (!w || !l || !u || !m || !ic) return false;

	c.resize(size_x*size_y*3);
	
	for (int i = 0;i < size_y;++i)
		for (int j = 0;j < size_x;++j) {
			//vybere texturu podle vysky terenu
			//pokud nesnezi, clenite textury terenu
			if (g.get_weather() != snowy) {
				if (h[i * size_y + j] == 0) image = w;
				else if ((h[i * size_y + j] > 0) && 
					(h[i * size_y + j] <= 85)) image = l;
				else if ((h[i * size_y + j] > 85) && 
					(h[i * size_y + j] <= 171)) image = u;
				else image = m;
			
			//kdyz snezi, je vsude snih a misto vody led
			} else {
				if (h[i * size_y + j] == 0) image = ic;
				else image = m;
			}

			//vyplni vektor 'pixelu'
			for (int k = 0;k < 3;++k)
				c[3 * (i * size_y + j) + k] = 
					((unsigned char*)(image->pixels))[3 * 
					(i * size_y + j) + k];

			image = 0;
		}

	SDL_FreeSurface(image);
	SDL_FreeSurface(w);
	SDL_FreeSurface(l);
	SDL_FreeSurface(u);
	SDL_FreeSurface(m);
	SDL_FreeSurface(ic);

	return true;
}

void imageloader_free(GLuint t)
{
	glDeleteTextures(1, &t);
}

