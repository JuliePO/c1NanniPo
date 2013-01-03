#ifndef HISTOGRAMME_H
#define HISTOGRAMME_H
#include <stdio.h>
#include <stdlib.h>

/************* Structure de l'histogramme *************/
typedef struct Histogramme {
	int canal; //rouge, bleu ou vert
	long values[256]; //les valeurs
}Histogramme;

/************* Appel des fonctions *************/

#endif
