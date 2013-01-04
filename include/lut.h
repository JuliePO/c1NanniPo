#ifndef LUT_H
#define LUT_H
#include <stdio.h>
#include <stdlib.h>

/************* Structure du LUT *************/
typedef struct LUT {
	// Définition de 3 tableaux pour chacune des composantes 
	// dont es valeurs vont de 0 à 255
	unsigned char tabLutR[256];
	unsigned char tabLutV[256];
	unsigned char tabLutB[256];

	//Calques 
	struct LUT *l_prev; //calque précédent
	struct LUT *l_next; //calque suivant

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

int initLUT (LUT*);

////effets sur l'images

//effets sur le contrast
void addCon(LUT*, int);
void dimCon(LUT*, int);
//effets sur la luminosité
void addLum(LUT*, int);
void dimLum(LUT*, int);
//effets sur les couleurs
void invert(LUT*);
void Sepia(LUT*, int);

#endif
