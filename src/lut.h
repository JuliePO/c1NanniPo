#ifndef LUT_H
#define LUT_H
#include <stdio.h>
#include <stdlib.h>

#include "image.h"
#include "calque.h"

/************* Structure du LUT *************/
typedef struct LUT {

	//numero de la lut
	int id;

	// Définition de 3 tableaux pour chacune des composantes 
	// dont es valeurs vont de 0 à 255
	unsigned char tabLutR[256];
	unsigned char tabLutV[256];
	unsigned char tabLutB[256];

	//pointeurs sur les Lut de la chaine
	struct LUT *l_prev; //lut précédent
	struct LUT *l_next; //lut suivant

}LUT;

//ensemble des LUT

typedef struct LLUT {

	//Taille de la liste
	size_t length;

	//Pointeur
	LUT *l_head; //pointeur vers le premier element
	LUT *l_tail; //pointeur vers le dernier element
}LLUT;

/************* Appel des fonctions *************/
LLUT* new_LLUT(void);
int initLUT(LLUT*, LUT*);
void applyLUT(Image*, LUT*);
LLUT* removeLut(LLUT*, int);

////effets sur l'images

//effets sur le contrast
void addContraste(LLUT*, int);
void dimContraste(LLUT*, int);
//effets sur la luminosité
void addLum(LLUT*, int);
void dimLum(LLUT*, int);
//effets sur les couleurs
void invert(LLUT*);
void B_W(Image*);
void colorize(LLUT*, int, int, int);
void sepia (LUT*, Image*);

#endif
