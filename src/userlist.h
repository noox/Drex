
#ifndef _USERLIST_H_
#define _USERLIST_H_

#include <string>

using namespace std;

void userlist_init();
void userlist_finish();
void name_file_init();
int make_user(string name);
int userlist_count();
string userlist_get_name(int userid);
string userlist_get_file_name(int userid);
string get_random_name(int t);

#endif

