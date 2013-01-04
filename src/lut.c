#include <stdlib.h>
#include <stdio.h>
//Appel de la structure d'une lut
#include "lut.h"

//initialisation de la lut
int initLUT(LUT* lut) {
	
	unsigned int i; // valeur entre 0-255

	for (i=0; i<256; i++ ) 
		{
			lut->tabLutR[i] = i;
			lut->tabLutV[i] = i;
			lut->tabLutB[i] = i;
		}

	return 0;
}	
