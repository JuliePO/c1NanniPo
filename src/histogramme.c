#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "outils.h"
#include "interface.h"
//Appel de la structure de l'histogramme
#include "histogramme.h"
#include "image.h"

/********* Création de l'histogramme *********/
Histogramme* createHistogramme(Image* img, int canal) {
	Histogramme* histo;
	int moyenne = 0, startIndex = 0, value = 0, maxValue, i, j;

	histo= (Histogramme*)malloc(sizeof(Histogramme));
	histo->canal = canal;
	
	//Initialisation du tableau
	for(i=0; i<256; i++) {
		histo->values[i] = 0;
	}
	
	if(canal>=0 || canal<=3) {
		// canal = 0 : Création de l'histogramme à partir des moyennes des valeurs RVB
		if(canal == 0) {
			for(i = 0; i < (img->heightImg) * (img->widthImg) * 3; i += 3) {
				//Moyenne des couleurs RVB
				moyenne = (((int)img->tabPixel[i] + (int)img->tabPixel[i+1] + (int)img->tabPixel[i+2]) / 3);
				//incrémente 
				histo->values[moyenne]++;
			}

			//Récupere la valeur maximal de l'histogramme
			maxValue = maxHisto(img, histo);

			//Réduit la taille de l'histogramme pour qu'il ne soit pas trop grand : la valeur la plus grande devient 100
			for (j = 0; j < 256; j++) {

				histo->values[j] = (100*(histo->values[j])/maxValue);
				histo->values[j] = 100 - (histo->values[j]);
			}

		}
		// canal != 0 : Création de l'histogramme en fonction d'un canal
		else {
			switch(canal) {
				//Rouge
				case 1 :
					break;
				//Vert
				case 2 :
					//Valeur Vert du pixel (deuxième valeur)
					startIndex = 1;
					break;
				//Bleu
				case 3 :
					//Valeur Bleu du pixel (troisième valeur)
					startIndex = 2;
					break;
			}
		
			for(i = startIndex; i < (img->heightImg) * (img->widthImg) * 3; i += 3){
				value= (int)img->tabPixel[i];
				histo->values[value]++;
			}

			//Récupere la valeur maximal de l'histogramme
			maxValue = maxHisto(img, histo);

			//Réduit la taille de l'histogramme pour qu'il ne soit pas trop grand : la valeur la plus grande devient 100
			for (j = 0; j < 256; j++) {

				histo->values[j] = (100*(histo->values[j])/maxValue);
				histo->values[j] = 100 - (histo->values[j]);
			}

		}
	}
	else {
		printf("Erreur : mode incompatible");
		return NULL;
	}

	return histo;
}

/********* Sauvegarde de l'histogramme sous forme d'une image ppm *********/
void SaveHisto(Histogramme* histo, char* name) {

	int i, j;
	
	//Création de la nouvelle image
	Image* histogramme = malloc(sizeof *histogramme);

	if(histogramme != NULL) {

		//Propriété de l'image
		histogramme->magicNumber[0] = 'P';
		histogramme->magicNumber[1] = '6';
		histogramme->heightImg = 100;
		histogramme->widthImg = 256;
		histogramme->maxValue = 256;

		//Alloue de la mémoire
		histogramme->tabPixel = (unsigned char*) malloc((histogramme->widthImg)*(histogramme->heightImg)*3*sizeof(unsigned char));

		if(histogramme->tabPixel != NULL) {
			
			//Parcours les valeurs de l'histogramme : ligne et colonne
			for(i = 0; i < (histogramme->heightImg); i++) {
			
				for(j = 0; j<256*3; j++) {

					if(i <= histo->values[j/3]) {
					
						histogramme->tabPixel[i*256*3+j] = 255;						

					}
					else {

						histogramme->tabPixel[i*256*3+j] = 0;

					}

				}
			}
			
			returnImage(histogramme);

			histogramme->widthImg = 256/2;

			if(saveImg(histogramme, name) == 1) {
				printf("L'histogramme a bien ete sauvegarde\n");
				free(histogramme);
			}
			else
				printf("Erreur dans la sauvegarde de l'histogramme\n");
		}
		else
			printf("Erreur : probleme dans la creation du tableau de pixel\n");
	}
	else
		printf("Erreur : probleme dans la creation de l'image\n");
	
}

/*void main(void) {

	Image image;
	Image* p = &image;
	char name[]="../images/daisuke.ppm";
	openImg(p, name);

	Histogramme* histo;

	histo = createHistogramme(p, 2);

	char name2[]="../images/histo.ppm";
	SaveHisto(histo, name2);
}*/

/********* Calcule de la valeur maximal de l'histogramme ************/
int maxHisto(Image* img, Histogramme* histo) {
	int i, maxValueH = 0;

	for(i = 0; i <(img->maxValue); i++) {
		if(maxValueH < histo->values[i])
			maxValueH = histo->values[i];
	}
	
	return maxValueH;
}

/******** Désallocation Histogramme ***********/
void removeHistogramme (Histogramme* histo) {
	free(histo);
}
