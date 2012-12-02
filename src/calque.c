#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//Appel de la structure de l'image
#include "image.h"
//Appel de la structure du calque
#include "calque.h"

/************* Création d'une nouvelle liste de calque *************/
LCalque* new_LCalque(void) {
	
	//Alloue de la mémoire 
	LCalque *p_calque = malloc(sizeof *p_calque);
	if (p_calque != NULL) {
		p_calque->length = 0;
		p_calque->p_head = NULL;
		p_calque->p_tail = NULL;
	}
	return p_calque;
}

/************* Ajouter un calque à la liste *************/
LCalque* addCalque(LCalque* p_lcalque, int opacity, Image* img) {

	// On vérifie si notre liste a été allouée
	if (p_lcalque != NULL) {
		//Création d'un nouveau calque
		struct calque *new_calque = malloc(sizeof *p_new); 

		// On vérifie si le malloc n'a pas échoué
		if (new_calque != NULL) {
			new_calque->opacity = opacity; 
			new_calque->image_src = img;
			new_calque->p_next = NULL; 

			// Cas où notre liste est vide (pointeur vers fin de liste à  NULL)
			if (p_lcalque->p_tail == NULL) {
				new_calque->p_prev = NULL; 
				 // Pointe la tête de la liste sur le nouveau calque
				p_lcalque->p_head = new_calque;
				// Pointe la fin de la liste sur le nouveau calque
				p_lcalque->p_tail = new_calque; 
			}
			// Cas où des éléments sont déjà présents dans la  liste
			else {
				// Relie le dernier calque de la liste au nouveau calque
				p_lcalque->p_tail->p_next = new_calque; 
				// Pointe p_prev du nouveau calque sur le dernier calque de la liste
				new_calque->p_prev = p_lcalque->p_tail; 
				// Pointe la fin de la liste sur le nouveau calque
				p_lcalque->p_tail = new_calque; 
			}
			// On augmente de 1 la taille de la liste
			p_lcalque->length++; 
		}
	}
	// on retourne notre nouvelle liste
	return p_lcalque; 
}


/************* Supprimer un calque selon sa position *************/
LCalque* removeCalque(LCalque* p_lcalque, int position) {

	// On vérifie si notre liste a été allouée
	if (p_lcalque != NULL) {

		//Création d'un calque temporaire
		struct calque *p_tmp = p_lcalque->p_head;
		int i = 1;

		// Parcours de la liste de calque, tant que i est inférieur à la position souhaitée
		while (p_tmp != NULL && i <= position) {

			if (position == i) {
				
				//Si c'est le dernier calque de la liste
				if (p_tmp->p_next == NULL) {
					
					//Pointe la fin de la liste sur le calque précédent
					p_lcalque->p_tail = p_tmp->p_prev;
					//Supprime le dernier calque ou lien du dernier calque vers le calque suivant est NULL
					p_lcalque->p_tail->p_next = NULL;
				}
			
				//Si c'est le premier calque de la liste
				else if (p_tmp->p_prev == NULL) {
					//Pointe la tête de la liste vers le calque suivant
					p_lcalque->p_head = p_tmp->p_next;
					//Le lien vers du deuxième calque vers le calque précédent est NULL ou Supprime le premier calque
 					p_lcalque->p_head->p_prev = NULL;
				}

				else {
					//Relie le calque suivant au calque précédent du calque que l'on veut supprmer 
					p_tmp->p_next->p_prev = p_tmp->p_prev;
					//Relie le calque précédent au calque suivant du calque que l'on veut supprmer 
					p_tmp->p_prev->p_next = p_tmp->p_next;
                		}
				//Libère espace mémoire
                		free(p_tmp);
				//Décrémente de un la taille de la liste
                		p_lcalque->length--;
            		}
           		 else {
                		p_tmp = p_tmp->p_next;
			}
            		i++;
		}
	}

	// on retourne notre nouvelle liste
	return p_lcalque; 
}
