#ifndef IMAGE_H
#define IMAGE_H
#include <stdio.h>
#include <stdlib.h>

/************* STRUCTURE DE L'IMAGE *************/
typedef struct Image {

	//Numero magic : identifie le type de fichier
	char magicNumber[2];
	
	//Les dimensions de l'images
	unsigned int heightImg;
	unsigned int widthImg;

	//Valeur maximal de la couleur, résolution de la couleur
	int maxValue;

	//Tableau de pixel
	unsigned char* tabPixel;
}Image;

/************* Appel de fonction *************/
void openImg(Image*, char*);
void returnImage(Image*);
void freeTabImg(Image*);
//void saveImg(Image*, char*);

#endif
