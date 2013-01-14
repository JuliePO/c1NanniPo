#include <stdlib.h>
#include <stdio.h>
//Appel de la structure d'une lut
#include "../include/lut.h"
#include "../include/image.h"
#include "../include/calque.h"


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
// il s'agit de remplacer les valeurs des pixels de l'image par celles de la lut
void remplirTab(Calque* calque, LUT* lut) {
	int i;
	for(i=0; i<((calque->image_src->heightImg)*(calque->image_src->widthImg)*3); i+=3){
		calque->image_src->tabPixel[i]=(unsigned char)(lut->tabLutR[calque->image_src->tabPixel[i]]);
		calque->image_src->tabPixel[i+1]=(unsigned char)(lut->tabLutV[calque->image_src->tabPixel[i+1]]);
		calque->image_src->tabPixel[i+2]=(unsigned char)(lut->tabLutB[calque->image_src->tabPixel[i+2]]);
	}
}

/******Effets**********/


//luminosité
//il s'agit d'ajouté une valeur positive choisie aux valeurs des pixels
//pour gagner en luminosité

void addLum(LUT* lut, int nb){
	int i;
 
 	for(i=0;i<256;i++)
 		{
 		if((lut->tabLutR[i]+nb)<0)
 			lut->tabLutR[i] = 0;
 		else if((lut->tabLutR[i]+nb)>255)
 			lut->tabLutR[i] = 255;
 		else
 			lut->tabLutR[i] = lut->tabLutR[i]+nb;
 			
 		if((lut->tabLutV[i]+nb)<0)
 			lut->tabLutV[i] = 0;
 		else if((lut->tabLutV[i]+nb)>255)
 			lut->tabLutV[i] = 255;
 		else
 			lut->tabLutV[i] = lut->tabLutV[i]+nb;
 			
 		if((lut->tabLutB[i]+nb)<0)
 			lut->tabLutB[i] = 0;
 		else if((lut->tabLutB[i]+nb)>255)
 			lut->tabLutB[i] = 255;
 		else
   			lut->tabLutB[i] = lut->tabLutB[i]+nb;
		}
}

//il s'agit d'ajouté une valeur négative choisie aux valeurs des pixels 
//pour diminuer la luminosité
void dimLum(LUT* lut, int nb){
	int i;
 
 	for(i=0;i<256;i++)
 		{
 		if((lut->tabLutR[i]-nb)<0)
 			lut->tabLutR[i] = 0;
 		else if((lut->tabLutR[i]-nb)>255)
 			lut->tabLutR[i] = 255;
 		else
 			lut->tabLutR[i] = lut->tabLutR[i]-nb;
 			
 		if((lut->tabLutV[i]-nb)<0)
 			lut->tabLutV[i] = 0;
 		else if((lut->tabLutV[i]-nb)>255)
 			lut->tabLutV[i] = 255;
 		else
 			lut->tabLutV[i] = lut->tabLutV[i]-nb;
 			
 		if((lut->tabLutB[i]-nb)<0)
 			lut->tabLutB[i] = 0;
 		else if((lut->tabLutB[i]-nb)>255)
 			lut->tabLutB[i] = 255;
 		else
   			lut->tabLutB[i] = lut->tabLutB[i]-nb;
		}
}




//couleur en négatifs, inversion des valeur des pixel par rapport à la 
//gamme de valeurs possible en RVB de 0 a 255
void invert(LUT* lut) {	
	int i;
   	for (i=0; i<256; i++) {
   		lut->tabLutR[i] = 255-lut->tabLutR[i];
   		lut->tabLutV[i] = 255-lut->tabLutV[i];
   		lut->tabLutB[i] = 255-lut->tabLutB[i];
   	}
} 	

/*Effet Sepia*/
void B_W(Image* img) {
	
	int i;

	for (i=0; i<((img->heightImg)*(img->widthImg))*3; i+=3) {
		img->tabPixel[i] = (img->tabPixel[i] + img->tabPixel[i+1] + img->tabPixel[i+2])/3;
		img->tabPixel[i+1] = (img->tabPixel[i] + img->tabPixel[i+1] + img->tabPixel[i+2])/3;
		img->tabPixel[i+2] = (img->tabPixel[i] + img->tabPixel[i+1] + img->tabPixel[i+2])/3;
	}
}

void colorize(LUT* lut, int R, int V, int B) {
	int i;
	for (i=0; i<256; i++) {

		if((lut->tabLutR[i]+R)<0)
 			lut->tabLutR[i] = 0;
 		else if((lut->tabLutR[i]+R)>255)
 			lut->tabLutR[i] = 255;
 		else
 			lut->tabLutR[i] = lut->tabLutR[i]+R;
 			
 		if((lut->tabLutV[i]+V)<0)
 			lut->tabLutV[i] = 0;
 		else if((lut->tabLutV[i]+V)>255)
 			lut->tabLutV[i] = 255;
 		else
 			lut->tabLutV[i] = lut->tabLutV[i]+V;
 			
 		if((lut->tabLutB[i]+B)<0)
 			lut->tabLutB[i] = 0;
 		else if((lut->tabLutB[i]+B)>255)
 			lut->tabLutB[i] = 255;
 		else
   			lut->tabLutB[i] = lut->tabLutB[i]+B;
	}
}

void sepia (LUT* lut, Image* img) {
	B_W(img);
	colorize(lut, 100, 50, 0);
}

int main(int argc, char const *argv[]) {

	printf("ça compile \n");
	return 0;
}