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

/************* Ajouter un calque à la liste  avec une image *************/
LCalque* addCalqueImg(LCalque* p_lcalque, float opacity, int mix, Image* img) {

	// On vérifie si notre liste a été allouée
	if (p_lcalque != NULL) {
		//Création d'un nouveau calque
		Calque* new_calque = malloc(sizeof *new_calque); 

		// On vérifie si le malloc n'a pas échoué
		if (new_calque != NULL) {
			new_calque->opacity = opacity; 
			new_calque->mix = mix; 
			new_calque->image_src = img;
			new_calque->p_next = NULL; 

			// Cas où notre liste est vide (pointeur vers fin de liste à  NULL) et id = 0
			if (p_lcalque->p_tail == NULL) {
				new_calque->id = 0;

				new_calque->p_prev = NULL; 
				 // Pointe la tête de la liste sur le nouveau calque
				p_lcalque->p_head = new_calque;
				// Pointe la fin de la liste sur le nouveau calque
				p_lcalque->p_tail = new_calque; 
			}
			// Cas où des éléments sont déjà présents dans la  liste
			else {
				new_calque->id = (p_lcalque->p_tail->id) + 1;
				
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

/************* Ajouter un calque vide *************/
LCalque* addCalque(LCalque* p_lcalque, float opacity, int mix) {

	int i;

	// On vérifie si notre liste a été allouée
	if (p_lcalque != NULL) {
		//Création d'un nouveau calque
		Calque* new_calque = malloc(sizeof *new_calque); 
		//Création de la nouvelle image
		Image* new_img = malloc(sizeof *new_img);
		
		//On vérifie si le malloc pour l'image n'a pas échoué
		if (new_img != NULL) {
		
			//Propriété de l'image
			new_img->magicNumber[0] = 'P';
			new_img->magicNumber[1] = '6';
			new_img->heightImg = p_lcalque->p_head->image_src->heightImg;
			new_img->widthImg = p_lcalque->p_head->image_src->widthImg;
			new_img->maxValue = p_lcalque->p_head->image_src->maxValue;
			
			//Alloue de la mémoire
			new_img->tabPixel = (unsigned char*)malloc( ((new_img->heightImg)*(new_img->widthImg)*3) * sizeof(unsigned char));

			//Remplie le tableau par des pixels blancs (225)
			for(i=0; i< (new_img->heightImg)*(new_img->widthImg)*3; i++) {
				new_img->tabPixel[i]=255;
			}


			// On vérifie si le malloc n'a pas échoué
			if (new_calque != NULL) {
				new_calque->opacity = opacity; 
				new_calque->mix = mix; 
				new_calque->p_next = NULL; 
				new_calque->image_src = new_img;
				new_calque->id = (p_lcalque->p_tail->id) + 1;

				// Relie le dernier calque de la liste au nouveau calque
				p_lcalque->p_tail->p_next = new_calque; 
				// Pointe p_prev du nouveau calque sur le dernier calque de la liste
				new_calque->p_prev = p_lcalque->p_tail; 
				// Pointe la fin de la liste sur le nouveau calque
				p_lcalque->p_tail = new_calque; 

				// On augmente de 1 la taille de la liste
				p_lcalque->length++; 
			}
			else {
				printf("Problème dans la creation du nouveau calque");
			}
		}
		else {
			printf("Problème dans la creation de la nouvealle image");
		}
	}

	// on retourne notre nouvelle liste
	return p_lcalque; 
}

/************* Modifier l'opacite d'un calque *************/
void modifOpacity (LCalque* p_lcalque, int position, float opacity){

	// On vérifie si notre liste a été allouée
	if (p_lcalque != NULL) {

		//Verifie que que le calque existe
		if(p_lcalque->length >= position + 1) {
		
			//Création d'un calque temporaire pour parcourir la liste de calque
			Calque *p_tmp = p_lcalque->p_head;

			// Parcours de la liste de calque
			while (p_tmp != NULL) {

				if (position == (p_tmp->id)) {				
					p_tmp->opacity = opacity; 
				}
				p_tmp = p_tmp->p_next;
			}
			//Libère espace mémoire
		        free(p_tmp);	
		}
		else
			printf("Ce calque n'existe pas\n");	
	}
}

/************* Modifier la fonction de mélange d'un calque *************/
void modifMix (LCalque* p_lcalque, int position, int mix){

	// On vérifie si notre liste a été allouée
	if (p_lcalque != NULL) {

		//Verifie que que le calque existe
		if(p_lcalque->length >= position+1) {

			//Vérifie qu'il s'agit bien d'une addition ou d'une multiplication
			if(mix == 0 || mix == 1) {

				//Création d'un calque temporaire pour parcourir la liste de calque
				Calque *p_tmp = p_lcalque->p_head;

				// Parcours de la liste de calque
				while (p_tmp != NULL) {

					if (position == (p_tmp->id)) {
									
						p_tmp->mix = mix; 
					}
					p_tmp = p_tmp->p_next;
				}
				//Libère espace mémoire
		        	free(p_tmp);
			}
			else
				printf("Erreur : ce n'est ni une addition, ni une multiplication : 0 = addition et 1 = multiplication\n");
		}
		else
			printf("Ce calque n'existe pas\n");
	}
}


/*void main(void){
	LCalque calque;
	LCalque* pc = &calque;
	pc = new_LCalque();

	Image image;
	Image* p = &image;
	char name[]="../images/image.ppm";
	openImg(p, name);

	pc = addCalqueImg(pc, 0, 0, p);
	pc = addCalque(pc, 0, 0);
	pc = addCalque(pc, 1, 1);
	

	if (pc != NULL)
	    {
		Calque *p_temp = pc->p_head;

		printf("ID : %d\n", pc->p_head->id);

		while (p_temp != NULL)
		{
			printf("%d %d\n %d\n", p_temp->image_src->heightImg, p_temp->image_src->widthImg, p_temp->image_src->maxValue);
			printf("Opacite : %f\n", p_temp->opacity);
			printf("ID : %d\n", p_temp->id);
			printf("\n");
		    fflush(stdout);
		    p_temp = p_temp->p_next;
		}
	    }

	printf("\n\n\nApres suppression : \n\n");
	pc = removeCalque(pc, 2);
	pc = removeCalque(pc, 1);
	pc = removeCalque(pc, 0);
	pc = removeCalque(pc, 2);


	if (pc != NULL)
	    {
		Calque *p_temp = pc->p_head;

		while (p_temp != NULL)
		{
			printf("Opacite : %f\n", p_temp->opacity);
			printf("ID : %d\n", p_temp->id);
			printf("\n");
		    fflush(stdout);
		    p_temp = p_temp->p_next;
		}
	    }

	printf("\n\n\nApres modification : \n\n");
	modifOpacity(pc, 0, 0.55);
	modifOpacity(pc, 1, 1);
	
	if (pc != NULL)
	    {
		Calque *p_temp = pc->p_head;

		while (p_temp != NULL)
		{
			printf("Opacite : %f\n", p_temp->opacity);
			printf("ID : %d\n", p_temp->id);
			printf("\n");
		    fflush(stdout);
		    p_temp = p_temp->p_next;
		}
	    }

}*/

/************ Fusionner les calques *************/
Image* fusionCalque(LCalque* p_lcalque) {

	int i;

	//Création de la nouvelle image
	Image* final_img = malloc(sizeof *final_img);
	
	//Propriété de l'image
	final_img->magicNumber[0] = 'P';
	final_img->magicNumber[1] = '6';
	final_img->heightImg = p_lcalque->p_head->image_src->heightImg;
	final_img->widthImg = p_lcalque->p_head->image_src->widthImg;
	final_img->maxValue = p_lcalque->p_head->image_src->maxValue;
	
	//Alloue de la mémoire
	final_img->tabPixel = (unsigned char*) malloc((final_img->widthImg)*(final_img->heightImg)*3*sizeof(unsigned char));
	
	// On vérifie si notre liste a été allouée
	if (p_lcalque != NULL) {
		
		//Vérifie qu'il y a plus d'un calque
		if(p_lcalque->length > 1) {
			
			//Création d'un calque temporaire pour parcourir la liste de calque
			Calque *p_tmp = p_lcalque->p_head;

			// Parcours de la liste de calque
			while (p_tmp != NULL) {

				//Si le mode de fusion est une ADDITION
				if(p_tmp->mix == 0) {

					if(p_tmp->id == 0) {

						//Parcours le tableau de pixel et multiplie par son opacite
						for(i=0; i< ((p_lcalque->p_head->image_src->widthImg) * (p_lcalque->p_head->image_src->heightImg)* 3); i++) {
							final_img->tabPixel[i] = (p_lcalque->p_head->image_src->tabPixel[i]) * (p_tmp->opacity);

						}
					}
					else {
						
						//Parcours le tableau de pixel et fusion des calques
						for(i=0; i< ((p_lcalque->p_head->image_src->widthImg) * (p_lcalque->p_head->image_src->heightImg)* 3); i++) {
							final_img->tabPixel[i] = (p_tmp->p_prev->image_src->tabPixel[i]) + (p_tmp->image_src->tabPixel[i]) * (p_tmp->opacity);
						}

					}

				}
				//Si le mode de fusion est une MULTIPLICATION
				else {

					if(p_tmp->id == 0) {

						//Parcours le tableau de pixel et multiplie par son opacite
						for(i=0; i< ((p_lcalque->p_head->image_src->widthImg) * (p_lcalque->p_head->image_src->heightImg)* 3); i++) {
							final_img->tabPixel[i] = (p_lcalque->p_head->image_src->tabPixel[i]) * (p_tmp->opacity);

						}
					}
					else {
						
						//Parcours le tableau de pixel et fusion des calques
						for(i=0; i< ((p_lcalque->p_head->image_src->widthImg) * (p_lcalque->p_head->image_src->heightImg)* 3); i++) {
							final_img->tabPixel[i] = (1 - (p_tmp->opacity)) * (p_tmp->p_prev->image_src->tabPixel[i]) + (p_tmp->image_src->tabPixel[i]) * (p_tmp->opacity);
						}
					}

				}
							
				p_tmp = p_tmp->p_next;
			}
			//Libère espace mémoire
			free(p_tmp);

		}
		//Si il y a qu'un seul calque
		else {

			//Parcours le tableau de pixel et multiplie par son opacite
			for(i=0; i< ((p_lcalque->p_head->image_src->widthImg) * (p_lcalque->p_head->image_src->heightImg)* 3); i++) {

				final_img->tabPixel[i] = (p_lcalque->p_head->image_src->tabPixel[i]) * (p_lcalque->p_head->opacity);

			}

		}

	}
	else
		printf("Cette liste de calque n'existe pas");

	returnImage(final_img);

	return final_img;
}

/************* Fusionner les images des calques : addition *************/
/************* Fusionner les images des calques : multiplication *************/

/************* Supprimer un calque selon sa position *************/
LCalque* removeCalque(LCalque* p_lcalque, int position) {

	// On vérifie si notre liste a été allouée
	if (p_lcalque != NULL) {

		//Verifie que que le calque existe
		if(p_lcalque->length >= position + 1) {

			//Vérifie s'il reste au moins un calque, si c'est le dernier calque alors ne le supprime pas
			if(p_lcalque->length > 1) {

				//Création d'un calque temporaire
				Calque *p_tmp = p_lcalque->p_head;

				// Parcours de la liste de calque, tant que id est inférieur à la position souhaitée
				while (p_tmp != NULL && (p_tmp->id) <= position) {

					if (position == (p_tmp->id)) {
				
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
							p_lcalque->p_head->id = 0;
						
							//Création d'un calque temporaire pour parcourir la liste de calque
							Calque *p_temp = p_lcalque->p_head->p_next;
							int i = 0;

							// Parcours de la liste de calque, tant que i est inférieur à la position souhaitée
							while (p_temp != NULL) {
								p_temp->id = ++i;
								p_temp = p_temp->p_next;
							}
							//Libère espace mémoire
							free(p_temp);
						}

						else {
							//Relie le calque suivant au calque précédent du calque que l'on veut supprmer 
							p_tmp->p_next->p_prev = p_tmp->p_prev;
							//Relie le calque précédent au calque suivant du calque que l'on veut supprmer 
							p_tmp->p_prev->p_next = p_tmp->p_next;

							//Création d'un calque temporaire pour parcourir la liste de calque à partir du calque suivant du calque que l'on veut supprimer
							Calque *p_temp = p_tmp->p_next;
							int i = p_tmp->p_prev->id;

							// Parcours de la liste de calque, tant que i est inférieur à la position souhaitée
							while (p_temp != NULL) {
								p_temp->id = ++i;
								p_temp = p_temp->p_next;
							}
							//Libère espace mémoire
							free(p_temp);

						}
						//Libère espace mémoire
						free(p_tmp);
						//Décrémente de un la taille de la liste
						p_lcalque->length--;

						break;
			    		}
			   		 else {
						p_tmp = p_tmp->p_next;
					}
				}
			}
			else
				printf("Erreur : impossible de supprimer le calque\n");
		}
		else
			printf("Ce calque n'existe pas\n");
	}

	// on retourne notre nouvelle liste
	return p_lcalque; 
}
