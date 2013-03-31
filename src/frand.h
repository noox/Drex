
#include <stdlib.h>

//nahodne cislo z intervalu -1..1
#ifndef DFRAND
#define DFRAND ((rand()/(float)RAND_MAX) * 2 - 1)
#endif

//nahodne cislo z intervalu 0..1
#ifndef FRAND 
#define FRAND (rand()/(float)RAND_MAX)
#endif

