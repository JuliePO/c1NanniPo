#include <stdlib.h>
#include <stdio.h>
//Appel de la structure d'une lut
#include "lut.h"
#include "image.h"

//initialisation de la lut
int initLUT(LUT* lut) {

	unsigned int i; // valeur entre 0-255

	for (i=0; i<256; i++ ) {
			lut->tabLutR[i] = i;
			lut->tabLutV[i] = i;
			lut->tabLutB[i] = i;
	}

	return 0;
}	

//application d'une LUT sur l'image

void remplirTab(Calque* calque, LUT* lut) {
	int i;
	for(i=0; i<((calque->image_src->heightImg)*(calque->image_src->largeurImg)*3); i+=3){
		//calque->img->tabPixel[i]=(unsigned char)(lut->tabLutR[calque->img->tabPixel[i]]);
		//calque->img->tabPixel[i+1]=(unsigned char)(lut->tabLutV[calque->img->tabPixel[i+1]]);
		//calque->img->tabPixel[i+2]=(unsigned char)(lut->tabLutB[calque->img->tabPixel[i+2]]);
	}
}

//Effets

void invert(LUT* lut) {	
	int i;
   	for (i=0; i<256; i++) {
   		lut->tabLutR[i] = 255-lut->tabLutR[i];
   		lut->tabLutV[i] = 255-lut->tabLutV[i];
   		lut->tabLutB[i] = 255-lut->tabLutB[i];
   	}
} 	