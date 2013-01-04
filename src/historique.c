#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//Appel de structures
#include "historique.h"
#include "calque.h"
#include "image.h"

/****** Initialisation de l'historique *******/
LHistorique* initHistory (void) {

	//Alloue de la mémoire 
	LHistorique *pile= malloc(sizeof *pile);
	if (pile != NULL) {

		pile->length = 0;
		pile->head = NULL;
	}
	return pile;
}

/****** Ajouter un nouvel évènement à la pile *******/

/* Liste des actions : 			*
* -1 : erreur, aucune action		*
*  0 : ajout d'un calque		*
*  1 : suppression d'un calque		*
*  2 : modification de l'opacite	*
*  3 : modification du mode de melange	*
*					*/


void addHistory (LHistorique* pile, LCalque* p_lcalque, int position, int action) {
	
	// On vérifie si notre liste a été allouée
	if (pile != NULL) {
	
		//Création d'un nouvel élément dans l'historique
		Historique* new_event = malloc(sizeof *new_event);
		
		// On vérifie si le malloc n'a pas échoué
		if (new_event != NULL) {

			//Création d'un nouveau calque
			Calque* new_calque = malloc(sizeof *new_calque); 

			if (new_calque != NULL) {
				
				// On vérifie si notre liste a été allouée
				if (p_lcalque != NULL) {

					//Si on retire un calque : stock juste l'id du calque, tout le reste à 0 ou NULL
					if (action == 1) {

						new_calque->id = position; //après mettre +1 car on se trouvera sur le calque precedent
						
						new_calque->opacity = 0; 
						new_calque->mix = 0; 
						new_calque->image_src = NULL;
						new_calque->p_prev = NULL;
						new_calque->p_next = NULL;
					}

					//Si c'est une modification ou un ajout de calque
					else if(action >= 2 || action == 0) {

						//Verifie que que le calque existe
						if(p_lcalque->length >= position + 1) {
		
							//Création d'un calque temporaire pour parcourir la liste de calque
							Calque *p_tmp = p_lcalque->p_head;

							// Parcours de la liste de calque
							while (p_tmp != NULL) {

								if (position == (p_tmp->id)) {				
								
									new_calque->opacity = p_tmp->opacity; 
									new_calque->mix = p_tmp->mix; 
									new_calque->image_src = p_tmp->image_src;
									new_calque->id = p_tmp->id;
									new_calque->p_prev = p_tmp->p_prev;
									new_calque->p_next = p_tmp->p_next;

								}
								p_tmp = p_tmp->p_next;
							}
							//Libère espace mémoire
							free(p_tmp);

						}
						else
							printf("Historique : Ce calque n'existe pas\n");
					}	

					//Ajoute le nouveau calque à la pile
					new_event->calqueH = new_calque;
					new_event->action = action;

					// Cas où notre liste est vide (pointeur vers la tête de liste est NULL) et id = 0
					if (pile->length == 0) {
							
						new_event->prev = NULL;
	
					}

					// Cas où des éléments sont déjà présents dans la  liste
					else {
						//Fait pointer cet évènement vers le sommet de la pile
						new_event->prev = pile->head;
					}

					//Fait pointer le sommet de la pile vers cet évènement
					pile->head = new_event;

					//Augmente la taille de la pile
					pile->length++;	
				}
				else 
					printf("Erreur d'allocation pour le liste de calque");

			}
			else 
				printf("Erreur d'allocation pour le calque");

		}
		else 
			printf("Erreur d'allocation pour le nouvel évènement de la pile");
	}
	else 
		printf("Erreur : l'historique n'existe pas");
}

/*void main (void) {

	LHistorique historique;
	LHistorique* ph = &historique;
	ph = initHistory();

	LCalque calque;
	LCalque* pc = &calque;
	pc = new_LCalque();

	Image image;
	Image* p = &image;
	char name[]="../images/image.ppm";
	openImg(p, name);

	pc = addCalqueImg(pc, 0, 0, p);
	addHistory(ph, pc, 0, 0);

	pc = addCalque(pc, 0, 0);
	addHistory(ph, pc, 1, 0);

	pc = addCalque(pc, 0, 1);
	addHistory(ph, pc, 2, 0);

	modifMix(pc, 0, 1);
	addHistory(ph, pc, 0, 3);

	modifOpacity(pc, 0, 0.55);
	addHistory(ph, pc, 0, 2);

	modifOpacity(pc, 1, 1);
	addHistory(ph, pc, 1, 2);

	pc = removeCalque(pc, 2);
	addHistory(ph, pc, 2, 1);

	if (pc != NULL)
	    {
		Calque *p_temp = pc->p_head;

		printf("\n\nListe des calques : \n\n");

		while (p_temp != NULL)
		{
			printf("Opacite : %f\n", p_temp->opacity);
			printf("ID : %d\n", p_temp->id);
			printf("\n");
		    fflush(stdout);
		    p_temp = p_temp->p_next;
		}

		printf("\n\n");
	    }


	AfficheHistory(ph);

	cancelHistory(ph, pc);

	if (pc != NULL)
	    {
		Calque *p_temp = pc->p_head;

		printf("\n\nListe des calques : \n\n");

		while (p_temp != NULL)
		{
			printf("Opacite : %f\n", p_temp->opacity);
			printf("ID : %d\n", p_temp->id);
			printf("\n");
		    fflush(stdout);
		    p_temp = p_temp->p_next;
		}

		printf("\n\n");
	    }

	AfficheHistory(ph);

	printf("\n");
}*/

/******** Afficher l'historique *******/
void AfficheHistory (LHistorique* pile) {

	Historique *p_temp = pile->head;
	int id;
	
	while (p_temp != NULL) {

		switch(p_temp->action) {
			
			case -1 : //ERREUR
				printf("Erreur\n");
				break;

			case 0 : //Ajout de calque
				id = p_temp->calqueH->id;
				printf("Ajout du calque %d\n", id);
				break;

			case 1 : //Suppression de calque
				id = p_temp->calqueH->id;
				printf("Suppression du calque %d\n", id);
				break;

			case 2 : //Modification de l'opacite
				id = p_temp->calqueH->id;
				printf("Modification de l'opacite du calque %d\n", id);
				break;

			case 3 : //Modification du mode de melange
				id = p_temp->calqueH->id;
				printf("Modification du mode de melange du calque %d\n", id);
				break;

		}
		printf("\n");
		p_temp = p_temp->prev;

	}

}


/********* Annuler une action ********/
void cancelHistory (LHistorique* pile, LCalque* p_lcalque) {

	// On vérifie si notre liste a été allouée
	if (pile != NULL) {
		
		// On vérifie que notre historique n'est pas vide
		if (pile->length != 0) {

			Historique* tmp_event = pile->head->prev;
			int position = pile->head->calqueH->id;
	
			// On vérifie si notre liste a été allouée
			if (p_lcalque != NULL) {

				//Si c'est un ajout de calque
				if(pile->head->action == 0) 
					removeCalque(p_lcalque, position);
				
				//Si c'est une supression d'un calque
				else if(pile->head->action == 1) {

					//Tant que l'historique n'est pas vide : on parcourt l'historique
					while(tmp_event != NULL){
			
						if (position == (tmp_event->calqueH->id)) {
							break;
						}
						tmp_event = tmp_event->prev;
					}

					addCalqueImg(p_lcalque, tmp_event->calqueH->opacity, tmp_event->calqueH->mix, tmp_event->calqueH->image_src);		

				}			
				else {
					//Tant que l'historique n'est pas vide : on parcourt l'historique
					while(tmp_event != NULL){
			
						if (position == (tmp_event->calqueH->id)) {
							break;
						}
						tmp_event = tmp_event->prev;
					}

					//Création d'un calque temporaire pour parcourir la liste de calque
					Calque *p_tmp = p_lcalque->p_head;

					// Parcours de la liste de calque
					while (p_tmp != NULL) {

						if (position == (p_tmp->id)) {		

							p_tmp->opacity = tmp_event->calqueH->opacity; 
							p_tmp->mix = tmp_event->calqueH->mix; 	
							p_tmp->image_src = tmp_event->calqueH->image_src; 

						}
						p_tmp = p_tmp->p_next;
					}
					//Libère espace mémoire
					free(p_tmp);	

				}

				Historique* event = pile->head;

				//Retire l'evenement de la pile
				event->action = 0;

				//Fait pointer cet le sommet vers l'évènement précédent
				pile->head = event->prev;

				//Supprime l'évènement
				free(event);

				//Décremente la taille de la pile
				pile->length--;

			}
			else 
				printf("Erreur d'allocation pour le liste de calque");

		}
		else 
			printf("Erreur : l'historique est vide, impossible de faire un retour");
	}
	else 
		printf("Erreur : l'historique n'existe pas");

}

/********* Désalocation de l'historique *********/
void removeHistory (LHistorique* pile) {
	// Si l'historique n'est pas vide
	if (pile->length != 0) {
		
		//Tant que l'historique n'est pas vide
		while(pile->head != NULL){

			Historique* event = pile->head;
			free(event->calqueH);
			pile->head = event->prev;
			free(event);
			
		}
	}
	free(pile);
}


