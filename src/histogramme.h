#ifndef HISTOGRAMME_H
#define HISTOGRAMME_H
#include <stdio.h>
#include <stdlib.h>
#include "image.h"

/************* Structure de l'histogramme *************/
typedef struct Histogramme {

	/* Canal : 	*
	* 0 : total	*
	* 1 : rouge	*
	* 2 : vert	*
	* 3 : bleu	*/
	int canal; 
	long values[256]; //les valeurs
}Histogramme;

/************* Appel des fonctions *************/
Histogramme* createHistogramme(Image*, int);
void SaveHisto(Histogramme*, char*);
int maxHisto(Image*, Histogramme*);
void removeHistogramme (Histogramme*);
#endif
