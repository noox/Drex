
#include "userlist.h"

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

//pro cteni adresaru
#include <sys/types.h>
#include <dirent.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;

vector<string> usernames, names;

//funkce na zjisteni poctu uzivatelu
int userlist_count() {
	return usernames.size();
}

//funkce pro overeni jmena uzivatele a pridani do vectoru
void process_userfilename (string n) {
	int l = n.length();
	if (l <= 4) return;
	if (n.substr (l -4) != ".usr") return;
	usernames.push_back (n);
}

//funkce pro zjisteni jmena uzivatele s priponou a cestou
string userlist_get_file_name (int userid) {
	if (usernames.size() > 0) return "users/" + usernames[userid];
	else return "";
}

//funkce pro zjisteni jmena uzivatele samotneho
string userlist_get_name (int userid) {
	if (usernames.size() > 0) return usernames[userid].substr (0, usernames[userid].length() - 4);
	else return "";
}

//funkce pripravujici adresar uzivatelu
void userlist_init() {
	usernames.clear();
	DIR* dirp;
	struct dirent* dp;
	dirp = opendir ("users/");
	if (!dirp) return;
	while (1) {
		dp = readdir (dirp);
		if (dp) {
			process_userfilename (dp->d_name);
		} else break;
	}
	closedir (dirp);
}

//vygeneruje nahodne jmeno ze seznamu jmen
string get_random_name (int t) {
	srand (time (0) );
	int r = rand() % (names.size() - 1);
	r += t;
	r %= names.size();
	//cout << "r: " << r << endl;
	string n = names[r];
	//cout << "n: " << n << endl;
	if (usernames.size() == 0) return n;
	//kontrola na shodu s existujicimi jmeny
	for (int i = 0;i < usernames.size();++i) {
		//cout << i << ".: " << n << " je " << userlist_get_name(i) << endl;
		//pokud takove jmeno jiz existuje
		if (n.compare (userlist_get_name (i) ) == 0) return get_random_name (t + 1);
	}
	return n;
}

//funkce pro cteni jmen ze souboru
void name_file_init() {
	fstream f ("data/names.txt", fstream::in);
	string line, name;

	while (getline (f, line, '\n') ) {
		stringstream ss (line);
		ss >> name;
		names.push_back (name);
	}
	f.close();
}

//vytvori uzivatelsky soubor pro noveho hrace
int make_user (string name) {
	if (name == "") return usernames.size() - 1;
	ofstream f;
	f.open ( ("users/" + name + ".usr").c_str() );
	f << "c\t0" << endl << "m" << endl << "d\t0" << endl << "w\t0" << endl << "f\t0" << endl << "s\t4" << endl << "z\t0" << endl;
	f.close();
	//a zresetuje seznam uzivatelu
	userlist_init();
	return userlist_count() - 1;
}

