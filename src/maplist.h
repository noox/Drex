
#ifndef _MAPLIST_H_
#define _MAPLIST_H_

#include <string>

using namespace std;

void maplist_init();
void maplist_finish();
int maplist_count();
string maplist_get_name(int mapid);
int maplist_get_mapid(string mapname);
const char* maplist_get_file_name(int mapid);

#endif

