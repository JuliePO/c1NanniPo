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

/* Liste des actions : 								*
* -2 : fantome : permet de stocker le calque pour permettre le redo		*
* -1 : erreur, aucune action							*
*  0 : ajout d'un calque							*
*  1 : suppression d'un calque							*
*  2 : modification de l'opacite						*
*  3 : modification du mode de melange						*
*  4 : Remplissage d'un calque							*
*  5 : Ajout d'une lut à la liste de lut					*
*  6 : Supprimer une lut							*
*  7 : Ajout de la lut sepia							*
*  8 : Suppression de la lut sepia						*
*										*/


int addHistory (LHistorique* pile, Calque* p_courant, int action) {
	
	// On vérifie si notre liste a été allouée
	if (pile != NULL) {
	
		//Création d'un nouvel élément dans l'historique
		Historique* new_event = malloc(sizeof *new_event);
		
		// On vérifie si le malloc n'a pas échoué
		if (new_event != NULL) {

			//Création d'un nouveau calque
			Calque* new_calque = malloc(sizeof *new_calque); 
			
			// On vérifie si notre calque a été allouée
			if (new_calque != NULL) {

				//Création de la nouvelle image
				Image* new_img = malloc(sizeof *new_img);

				if(new_img != NULL) {
				
					// On vérifie si notre calque a été allouée
					if (p_courant != NULL) {
	
						new_calque->opacity = p_courant->opacity; 
						new_calque->mix = p_courant->mix; 
						new_calque->id = p_courant->id;
						new_calque->p_prev = p_courant->p_prev;
						new_calque->p_next = p_courant->p_next;

						new_calque->image_src = new_img;

						if(copyImg(new_img, p_courant->image_src) == 0) {
							printf("Probleme au moment de la copie de l'image\n");
							return 0;
						}

						//Création de la liste de lut
						LLut* new_llut = malloc(sizeof *new_llut);

						// On vérifie si le malloc n'a pas échoué
						if(new_llut != NULL) {
				
							//Initialisation de la liste de lut
							new_llut = new_LLut(new_llut);
							new_calque->p_llut = new_llut;

							if(copyLLut(p_courant->p_llut, new_llut) == 0) {
								printf("Probleme au moment de la copie de la liste de luts\n");
								return 0;
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
						else {
							printf("Erreur d'allocation pour la liste de lut");
							return 0;
						}
					}
					else {
						printf("Erreur d'allocation pour le calque courant\n");
						return 0;
					}
				}
				else {
					printf("Erreur d'allocation pour l'image du calque\n");
					return 0;
				}

			}
			else {
				printf("Erreur d'allocation pour le calque de l'historique\n");
				return 0;
			}

		}
		else {
			printf("Erreur d'allocation pour le nouvel évènement de la pile\n");
			return 0;
		}
	}
	else {
		printf("Erreur : l'historique n'existe pas\n");
		return 0;
	}
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
	
	printf("\n");
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

			case 4 : //Modification du mode de melange
				id = p_temp->calqueH->id;
				printf("Remplissage ou passage en noir et blanc du calque %d\n", id);
				break;

			case 5 : //Ajout d'une lut
				id = p_temp->calqueH->id;
				printf("Ajout d'une lut dans le liste du luts du calque %d\n", id);
				break;

			case 6 : //Suppression de lut
				id = p_temp->calqueH->id;
				printf("Suppression de la derniere lut du calque %d\n", id);
				break;

			case 7 : //Suppression de lut
				id = p_temp->calqueH->id;
				printf("Ajout d'une lut dans le liste du luts du calque %d\n", id);
				break;

			case 8 : //Suppression de lut
				id = p_temp->calqueH->id;
				printf("Suppression de la derniere lut du calque %d\n", id);
				break;


		}
		p_temp = p_temp->prev;

	}

}


/********* Annuler une action ********/
int cancelHistory (LHistorique* pile, LCalque* p_lcalque, LHistorique* redo) {

	// On vérifie si notre liste a été allouée
	if (pile != NULL) {
		
		// On vérifie que notre historique n'est pas vide
		if (pile->length > 1) {

			Historique* tmp_event = pile->head->prev;
			int position = pile->head->calqueH->id;
	
			// On vérifie si notre liste a été allouée
			if (p_lcalque != NULL) {
				
				//Supression
				if(pile->head->action == 1) {
					//Tant que l'historique n'est pas vide : on parcourt l'historique
					while(tmp_event != NULL){
			
						if (position == (tmp_event->calqueH->id)) {
							break;
						}
						tmp_event = tmp_event->prev;
					}

					returnImage(tmp_event->calqueH->image_src);

					//Ajout dans l'historique
					if(addHistory(redo, tmp_event->calqueH, 0) == 0) {
						printf("probleme au moment de l'ajout de l'element dans l'historique redo\n");
						return 0;
					}

					addCalqueImgId(p_lcalque, tmp_event->calqueH->opacity, tmp_event->calqueH->mix, tmp_event->calqueH->image_src, tmp_event->calqueH->id, tmp_event->calqueH->p_llut);

				}
				//Ajout de calque
				else if(pile->head->action == 0) {

					//Ajout dans l'historique
					if(addHistory(redo, p_lcalque->p_tail, 1) == 0) {
						printf("probleme au moment de l'ajout de l'element dans l'historique redo\n");
						return 0;
					}

					removeCalque(p_lcalque, p_lcalque->p_tail); //car le calque ajouter sera toujours en fin de liste
					
				}
				//Ajout d'une lut
				else if(pile->head->action == 5) {

					//Création d'un calque temporaire pour parcourir la liste de calque
					Calque *p_tmp = p_lcalque->p_head;

					// Parcours de la liste de calque
					while (p_tmp != NULL) {

						if (position == (p_tmp->id)) {
							break;
						}
						p_tmp = p_tmp->p_next;
					}

					//Ajout dans l'historique
					if(addHistory(redo, p_tmp, 6) == 0) {
						printf("probleme au moment de l'ajout de l'element dans l'historique redo\n");
						return 0;
					}

					removeLut(p_tmp->p_llut, p_tmp->p_llut->l_tail->id);

					
				}
				//Suppression d'une lut
				else if(pile->head->action == 6) {

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
							break;
						}
						p_tmp = p_tmp->p_next;
					}

					//Ajout dans l'historique
					if(addHistory(redo, p_tmp, 5) == 0) {
						printf("probleme au moment de l'ajout de l'element dans l'historique redo\n");
						return 0;
					}

					//Création de la nouvelle lut
					Lut *new_lut = malloc(sizeof *new_lut);
					
					//On vérifie que l'allocation a été faite
					if (new_lut != NULL) {

						//Ajout de la lut à la liste de lut
						addLUT(p_tmp->p_llut,new_lut);

						//Copie la lut avec l'ancienne lut
						if(copyLut(tmp_event->calqueH->p_llut->l_tail, new_lut) == 0) {
							printf("Probleme au moment de la copie de la lut");
							return 0;
						}
					}
					else {
						printf("Erreur au moment de la création de la lut\n");
						return 0;
					}
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
							int action;

							//Modification de l'opacite
							if(p_tmp->opacity != tmp_event->calqueH->opacity) {
								action = 2;
								p_tmp->opacity = tmp_event->calqueH->opacity;
							} 
							//Modification du mode d'operation
							else if(p_tmp->mix != tmp_event->calqueH->mix) {
								action = 3;
								p_tmp->mix = tmp_event->calqueH->mix;
							}
							//Remplissage ou passage en noir et blanc
							else {
								action = 4;
								p_tmp->image_src = tmp_event->calqueH->image_src;
							}

							//Ajout dans l'historique
							if(addHistory(redo, p_tmp, action) == 0) {
								printf("probleme au moment de l'ajout de l'element dans l'historique redo\n");	
								return 0;
							}
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
			else {
				printf("Erreur d'allocation pour le liste de calque\n");
				return 0;
			}

		}
		else {
			printf("Erreur : l'historique est vide, impossible de faire un retour\n");
			return 0;
		}
	}
	else {
		printf("Erreur : l'historique n'existe pas\n");
		return 0;
	}

}

/********* Redo *********/
void redoHistory (LHistorique* redo, LCalque* p_lcalque, LHistorique* pile) {
	cancelHistory (redo, p_lcalque, pile);
}

/********* Désalocation de l'historique *********/
void removeHistory (LHistorique* pile) {
	// Si l'historique n'est pas vide
	if (pile->length != 0) {
		
		//Tant que l'historique n'est pas vide
		while(pile->head != NULL){

			Historique* event = pile->head;
			freeTabImg(event->calqueH->image_src);
			free(event->calqueH);
			pile->head = event->prev;
			free(event);
			
		}
	}
	free(pile);
}


