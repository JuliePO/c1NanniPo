#ifndef CALQUE_H
#define CALQUE_H
#include <stdio.h>
#include <stdlib.h>
#include <image.h>

// STRUCTURE DU CALQUE
struct calque {
	
	//Paramètre d'opacité : 0 ou 1
	int opacity; 

	//Image source
	Image image_src;

	//type d'opération

	//liste de LUT

	//Calques 
	struct calque *p_prev; //calque précédent
	struct calque *p_next; //calque suivant
};

typedef struc LCalque {

	//Taille de la liste
	size_t lenght;

	//Pointeur
	struct calque *p_head; //pointeur vers le premier element
	struct calque *p_tail; //pointeur vers le dernier element
}LCalque;

//Appel de fonction
LCalque* new_LCalque(void);
LCalque* addCalque(LCalque*, int, Image);
LCalque* removeCalque(LCalque* p_lcalque, int position);

#endif
