
#ifndef _MAPLIST_H_
#define _MAPLIST_H_

#include <string>
using namespace std;

void maplist_init();
int maplist_count();
string maplist_get_name(int mapid);
string maplist_get_file_name(int mapid);

#endif

