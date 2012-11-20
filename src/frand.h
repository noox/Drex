
#include <stdlib.h>

#ifndef DFRAND //nahodne cislo z intervalu -1..1
#define DFRAND ((rand()/(float)RAND_MAX)*2-1)
#endif

#ifndef FRAND //0..1
#define FRAND (rand()/(float)RAND_MAX)
#endif

