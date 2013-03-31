
#include <stdlib.h>

//pro cteni adresaru
#include <sys/types.h>
#include <dirent.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

#include "maplist.h"

vector<string> maps;

//funkce na zjisteni poctu map
int maplist_count()
{
	return maps.size();
}

//funkce pro overeni jmena mapy a pridani do vectoru
void process_mapfilename(string n)
{
	int l = n.length();
	if (l <= 4) return;
	if (n.substr(l - 4) != ".map") return;
	maps.push_back(n);
}

//funkce pro zjisteni nazvu mapy s priponou a cestou
const char* maplist_get_file_name(int mapid)
{
	if (maps.size() > 0) {
		string s = "maps/" + maps[mapid];
		const char* x = s.c_str();
		return x;
	} else return "";
}

//funkce pro zjisteni nazvu mapy samotneho
string maplist_get_name(int mapid)
{
	if (maps.size() > 0)
		return maps[mapid].substr(0, maps[mapid].length() - 4);
	else return "";
}

//funkce pripravujici adresar map
void maplist_init()
{
	maplist_finish();
	DIR* dirp;
	struct dirent* dp;
	dirp = opendir("maps/");
	if (!dirp) return;
	while (1) {
		dp = readdir(dirp);
		if (dp) {
			process_mapfilename(dp->d_name);
		} else break;
	}
	closedir(dirp);
}

void maplist_finish()
{
	maps.clear();
}

