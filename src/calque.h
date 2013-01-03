#ifndef CALQUE_H
#define CALQUE_H
#include <stdio.h>
#include <stdlib.h>
#include "image.h"
#include "LUT.h"

/************* STRUCTURE DU CALQUE *************/
typedef struct Calque {

	//Le numéro du calque (premier calque = 0)
	int id;
	
	//Paramètre d'opacité entre 0 et 1
	float opacity; 

	//Image source
	Image* image_src;

	//type d'opération : addition = 0 et multiplication = 1
	int mix;

	//liste de LUT
	LLUT* list_lut;

	//Calques 
	struct Calque *p_prev; //calque précédent
	struct Calque *p_next; //calque suivant
}Calque;

/************* STRUCTURE DE LA LISTE DE CALQUE *************/
typedef struct LCalque {

	//Taille de la liste
	size_t length;

	//Pointeur
	Calque *p_head; //pointeur vers le premier element
	Calque *p_tail; //pointeur vers le dernier element
}LCalque;

/************* Appel de fonction *************/
LCalque* new_LCalque(void);
LCalque* addCalqueImg(LCalque*, float, int, Image*);
LCalque* addCalque(LCalque*, float, int);
LCalque* removeCalque(LCalque*, int);
void modifOpacity (LCalque*, int, float);
void modifMix (LCalque*, int, int);
#endif
