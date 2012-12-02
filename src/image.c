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


/************* Ouverture de l'image ************/

void openImg(Image* img, char* nameImg){

	FILE* image = NULL;
	image = fopen(nameImg, "r");
	
	if(image == NULL){
		printf("Erreur : Impossible d'ouvrir l'image");
		return NULL;
	}
	else{

		//Récupère le type d'image
		fscanf(image, "%s\n", &(img->magicNumber));
		//Si ce n'est pas un ppm, arrete la fonction 
		if(img->magicNumber != "P6"){
			printf("L'image n'est pas au bont format");
			return;
		else{
			
			//Récupère la hauteur, la largeur et la résolution de la couleur
			fscanf(image, "%d %d\n%d\n", &(img->heightImg), &(img->widthImg), &(img->maxValue));
			
			//Alloue de la mémoire
			img->tabPixel = (unsigned char*)malloc( ((img->heightImg)*(img->widthImg)*3) * sizeof(unsigned char));
			//Récupère les pixels et les stock dans un tableau de taille : hauteur * largeur * 3 car chaque pixel est composé de 3 couleurs
			fread(img->tabPixel, sizeof(unsigned char),(img->heightImg)*(img->widthImg)*3,image);

			// On ferme le vide le buffer et on ferme l'image
			fflush(image);
			fclose(image);
		}
	}
}


/************* Retourner l'image ************/

void returnImage(calque* c, unsigned char* tab) {
	int i, j, k=0;
	// On parcourt les lignes du tableau à l'envers
	for(i=(c->img->heightImg); i>=0; i--) {

		// puis on parcourt les colonnes du tableau
		for(j=0; j<(c->img->widthImg); j++) {

			// On retourne le tableau de l'image de haut en bas
			tab[k++] = c->image_src->tabPixel[i*(c->img->widthImg)*3+j*3];
			tab[k++] = c->image_src->tabPixel[i*(c->img->widthImg)*3+j*3+1];
			tab[k++] = c>image_src->tabPixel[i*(c->img->widthImg)*3+j*3+2];

		}
	}
	return;
}

/************* Libéré l'espace mémoire *************/
void freeTabImg(Image* img) {
	free(img->tabPixel);
	return;
}	
	
