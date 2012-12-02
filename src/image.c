//ficher servant à déclarer les fonctions qui feront des opérations sur les images
//il faut aussi creer un .h 

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//Appel de la structure de l'image
#include "image.h"

//Structure IMAGE

/*typedef struct structure_image 
	{
	// Numéro de variante
	char numVar;
	
	// Hauteur et largeur de l'image
	unsigned int hauteurImg;
	unsigned int largeurImg;
	
	// Valeur maximale
	int valMax;
	
	// Valeur des pixels
	unsigned char* tabPixel; 
	}str_Img;*/

void openImg(Image* img, char* nameImg){

	FILE* image = NULL;
	image = fopen(nameImg, "w");
	
	if(image == NULL){
		printf("Erreur : Impossible d'ouvrir l'image");
		return NULL;
	}
	else{

		//Récupère le type d'image
		fscanf(image, "%s\n", img->magicNumber);
		//Si ce n'est pas un ppm, arrete la fonction 
		if(img->magicNumber != "P6"){
			printf("L'image n'est pas au bont format");
			return;
		else{
			
			//Récupère la hauteur, la largeur et la résolution de la couleur
			fscanf(image, "%d %d\n%d\n", img->heightImg, img->widthImg, img->maxValue);
			//Récupère les pixels et les stock dans un tableau de taille : hauteur * largeur * 3 car chaque pixel est composé de 3 couleurs
			fread(img->tabPixel, sizeof(unsigned char),(img->heightImg)*(img->widthImg)*3,image);
			fclose(image);
		}
	}
}
