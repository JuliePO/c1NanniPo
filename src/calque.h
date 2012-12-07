#ifndef CALQUE_H
#define CALQUE_H
#include <stdio.h>
#include <stdlib.h>
#include "image.h"

/************* STRUCTURE DU CALQUE *************/
typedef struct Calque {
	
	//Paramètre d'opacité : 0 ou 1
	int opacity; 

	//Image source
	Image* image_src;

	//type d'opération

	//liste de LUT

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
LCalque* addCalque(LCalque*, int, Image*);
LCalque* removeCalque(LCalque* p_lcalque, int position);

#endif
