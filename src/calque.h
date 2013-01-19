#ifndef CALQUE_H
#define CALQUE_H
#include <stdio.h>
#include <stdlib.h>
#include "image.h"
#include "lut.h"

/************* STRUCTURE DU CALQUE *************/
typedef struct Calque {

	//Le numéro du calque (premier calque = 0)
	int id;
	
	//Paramètre d'opacité entre 0 et 1
	float opacity; 

	//Image source
	Image* image_src;

	//type d'opération : addition = 0 et multiplication = 1 (soustraction : 2)
	int mix;

	//liste de LUT
	LLut* p_llut;

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
int addCalqueImg(LCalque*, float, int, char* nameImg);
int addCalque(LCalque*, float, int);
int addCalqueImgId(LCalque*, float, int, Image*, int, LLut* p_llut);

int modifOpacity (Calque*, float);
int modifMix (Calque*, int);

Calque* navCalque (LCalque*, Calque*, int);
int remplirCalque(Calque*, int, int, int);

LCalque* removeCalque(LCalque*, Calque*);

void afficheLCalque(LCalque*);

int calqueCourant(Calque*, Image*);
Image* fusionCalque(LCalque*);
int valeur_propre(int);

void removeLCalque(LCalque*);
#endif
