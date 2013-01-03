#ifndef LUT_H
#define LUT_H
#include <stdio.h>
#include <stdlib.h>

/************* Structure du LUT *************/
typedef struct LUT {
	// Définition de 3 tableaux pour chacune des composantes!
	unsigned char tabLutR[256];
	unsigned char tabLutV[256];
	unsigned char tabLutB[256];

	//Calques 
	struct LUT *l_prev; //calque précédent
	struct LUT *l_next; //calque suivant

}LUT;


typedef struct LLUT {

	//Taille de la liste
	size_t length;

	//Pointeur
	LUT *l_head; //pointeur vers le premier element
	LUT *l_tail; //pointeur vers le dernier element
}LLUT;

/************* Appel des fonctions *************/

#endif
