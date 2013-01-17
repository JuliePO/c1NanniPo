#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//Appel de la structure de l'image
#include "image.h"
//Appel de la structure de la lut
#include "lut.h"

/************* Création d'une nouvelle liste de calque *************/
LLut* new_LLut(LLut* p_llut) {
	
	if (p_llut != NULL) {
		p_llut->length = 0;
		p_llut->l_head = NULL;
		p_llut->l_tail = NULL;
	}

	//Rajout de la lut fantome
	Lut *new_lut = malloc(sizeof *new_lut);

	if (new_lut != NULL) {
		if(addLUT(p_llut,new_lut) == 0) {
			printf("Erreur au moment de la creation de la lut fantome\n");
		}
	}
	else {
		printf("Probleme d'allocation de la lut\n");
		return 0;
	}

	return p_llut;
}

/************* Ajout d'une lut dans la liste de lut *************/
int addLUT(LLut* p_llut, Lut* new_lut) {

	if (p_llut != NULL)	{

		if (new_lut != NULL) {

			//initialisaton des parametres

			unsigned int i; // valeur entre 0-255

			for (i=0; i<256; i++ ) {
					new_lut->tabLutR[i] = i;
					new_lut->tabLutV[i] = i;
					new_lut->tabLutB[i] = i;
			} 


			//ajout a liste

			// Cas où notre liste est vide (pointeur vers fin de liste à  NULL) et id = 0
			if (p_llut->l_tail == NULL) {
				new_lut->id = 0;

				new_lut->l_prev = NULL; 
				 // Pointe la tête de la liste sur le nouveau lut
				p_llut->l_head = new_lut;
				// Pointe la fin de la liste sur le nouveau lut
				p_llut->l_tail = new_lut; 
			}
			// Cas où des éléments sont déjà présents dans la  liste
			else {
				new_lut->id = (p_llut->l_tail->id) + 1;
				
				// Relie le dernier lut de la liste au nouveau lut
				p_llut->l_tail->l_next = new_lut; 
				// Pointe p_prev du nouveau lut sur le dernier lut de la liste
				new_lut->l_prev = p_llut->l_tail; 
				// Pointe la fin de la liste sur le nouveau lut
				p_llut->l_tail = new_lut; 
			}
			// On augmente de 1 la taille de la liste
			p_llut->length++; 

		}
		else {
			printf("OOps..cette lut n'existe pas \n");
			return 0;
		}

	}
	else {
		printf("OOps... Cette liste de lut n'existe pas \n");
		return 0;
	}
	
	//on retourne la liste
	return 1;
}

/************* Application d'une LUT sur l'image *************/
// il s'agit de remplacer les valeurs des pixels de l'image par celles de la lut
void applyLUT(Image* img, Lut* lut) {
	int i;
	for(i=0; i<((img->heightImg)*(img->widthImg)*3); i+=3){
		img->tabPixel[i]=(lut->tabLutR[img->tabPixel[i]]);
		img->tabPixel[i+1]=(lut->tabLutV[img->tabPixel[i+1]]);
		img->tabPixel[i+2]=(lut->tabLutB[img->tabPixel[i+2]]);
	}
}

/*********** Afficher le liste de lut d'un calque ****************/
void afficheLLut(LLut* p_llut) {
	if (p_llut != NULL) {
		//Création du calque temporaire pour parcourrir la liste de calque
		Lut *lut_tmp = p_llut->l_head;

		printf("\n");
		//Parcourt la liste de calque
		while (lut_tmp != NULL) {
			printf("ID : %d\n", lut_tmp->id);
			printf("\n");
		    	lut_tmp = lut_tmp->l_next;
		}
		free(lut_tmp);
	}
}

/************* Supprimer une lut selon sa position *************/
LLut* removeLut(LLut* p_llut, int position) {

	// On vérifie si notre liste a été allouée
	if (p_llut != NULL) {

		//Verifie que que le lut existe
		if(p_llut->length >= position) {

			//Vérifie s'il reste au moins un lut, si c'est le dernier lut alors ne le supprime pas
			if(p_llut->length > 1) {

				//Création d'un lut temporaire
				Lut *p_tmp = p_llut->l_head;

				// Parcours de la liste de lut, tant que id est inférieur à la position souhaitée
				while (p_tmp != NULL && (p_tmp->id) <= position) {

					if (position == (p_tmp->id)) {
				
						//Si c'est le dernier lut de la liste
						if (p_tmp->l_next == NULL) {
					
							//Pointe la fin de la liste sur le lut précédent
							p_llut->l_tail = p_tmp->l_prev;
							//Supprime le dernier lut ou lien du dernier lut vers le lut suivant est NULL
							p_llut->l_tail->l_next = NULL;
						}
			
						//Si c'est le premier lut de la liste
						else if (p_tmp->l_prev == NULL) {
							//Pointe la tête de la liste vers le lut suivant
							p_llut->l_head = p_tmp->l_next;
							//Le lien vers du deuxième lut vers le lut précédent est NULL ou Supprime le premier lut
		 					p_llut->l_head->l_prev = NULL;
							p_llut->l_head->id = 0;
						
							//Création d'un lut temporaire pour parcourir la liste de lut
							Lut *p_temp = p_llut->l_head->l_next;
							int i = 0;

							// Parcours de la liste de lut, tant que i est inférieur à la position souhaitée
							while (p_temp != NULL) {
								p_temp->id = ++i;
								p_temp = p_temp->l_next;
							}
							//Libère espace mémoire
							free(p_temp);
						}

						else {
							//Relie la lut suivant au lut précédent de la lut que l'on veut supprmer 
							p_tmp->l_next->l_prev = p_tmp->l_prev;
							//Relie la lut précédent au lut suivant de la lut que l'on veut supprmer 
							p_tmp->l_prev->l_next = p_tmp->l_next;

							//Création d'une lut temporaire pour parcourir la liste de lut à partir de la lut suivante du lut que l'on veut supprimer
							Lut *p_temp = p_tmp->l_next;
							int i = p_tmp->l_prev->id;

							// Parcours de la liste de lut, tant que i est inférieur à la position souhaitée
							while (p_temp != NULL) {
								p_temp->id = ++i;
								p_temp = p_temp->l_next;
							}
							//Libère espace mémoire
							free(p_temp);

						}
						//Libère espace mémoire
						free(p_tmp);
						//Décrémente de un la taille de la liste
						p_llut->length--;

						break;
			    		}
			   		 else {
						p_tmp = p_tmp->l_next;
					}
				}
			}else
				printf("Erreur : impossible de supprimer la lut\n");
		}else
			printf("Oops! Cette lut n'existe pas\n");
	}

	// on retourne notre nouvelle liste
	return p_llut; 
}

/************* Copie liste de lut pour l'historique *************/
int copyLLut(LLut* p_llut, LLut* new_llut) {
	
	if(p_llut != NULL) {
		
		if(new_llut != NULL) {

			//Création d'une lut temporaire pour parcourir la liste de lut
			Lut *lut_tmp = p_llut->l_head;

			//Parcourt la liste de lut 
			while (lut_tmp != NULL) {
				
				Lut *new_lut = malloc(sizeof *new_lut);

				if (new_lut != NULL) {
		
					addLUT(new_llut,new_lut);

					if(copyLut(lut_tmp, new_lut) == 0) {
						printf("Probleme au moment de la copie des lut\n");
						return 0;
					}

				}
				else {
					printf("Erreur d'allocation de la lut");
					return 0;
				}
			    	lut_tmp = lut_tmp->l_next;
			}
		}
		else {
			printf("Cette liste de lut n'existe pas\n");
			return 0;
		}
	}
	else {
		printf("Cette liste de lut n'existe pas\n");
		return 0;
	}

	return 1;

}

/************* Copie d'une lut *************/
int copyLut(Lut* p_lut, Lut* new_lut) {
	int i;
	
	if(p_lut != NULL) {
		
		if(new_lut != NULL) {
			
			new_lut->id = p_lut->id;
					
			//Copie les tableaux
			for(i=0;i<256;i++) {
				new_lut->tabLutR[i] = p_lut->tabLutR[i];
				new_lut->tabLutV[i] = p_lut->tabLutV[i];
				new_lut->tabLutB[i] = p_lut->tabLutB[i];
			}

		}
		else {
			printf("La lut n'existe pas\n");
			return 0;
		}
	}
	else {
		printf("La lut n'existe pas\n");
		return 0;
	}
	return 1;
}

/******Effets**********/


//luminosité
//il s'agit d'ajouté une valeur positive choisie aux valeurs des pixels
//pour gagner en luminosité

void addLum(LLut* p_llut, int nb){

	Lut *new_lut = malloc(sizeof *new_lut);

	if (new_lut != NULL) {
		
		addLUT(p_llut,new_lut);

		int i;
	 	for(i=0;i<256;i++) {
	 		if((new_lut->tabLutR[i]+nb)<0)
	 			new_lut->tabLutR[i] = 0;
	 		else if((new_lut->tabLutR[i]+nb)>255)
	 			new_lut->tabLutR[i] = 255;
	 		else
	 			new_lut->tabLutR[i] = new_lut->tabLutR[i]+nb;
	 			
	 		if((new_lut->tabLutV[i]+nb)<0)
	 			new_lut->tabLutV[i] = 0;
	 		else if((new_lut->tabLutV[i]+nb)>255)
	 			new_lut->tabLutV[i] = 255;
	 		else
	 			new_lut->tabLutV[i] = new_lut->tabLutV[i]+nb;
	 			
	 		if((new_lut->tabLutB[i]+nb)<0)
	 			new_lut->tabLutB[i] = 0;
	 		else if((new_lut->tabLutB[i]+nb)>255)
	 			new_lut->tabLutB[i] = 255;
	 		else
	   			new_lut->tabLutB[i] = new_lut->tabLutB[i]+nb;
	   }
	}else {
		printf("Erreur d'allocation de la lut \n");
	}

}

//il s'agit d'ajouté une valeur négative choisie aux valeurs des pixels 
//pour diminuer la luminosité
void dimLum(LLut* p_llut, int nb){

	Lut *new_lut = malloc(sizeof *new_lut);

	if (new_lut != NULL) {
		
		addLUT(p_llut,new_lut);

		int i;
 
	 	for(i=0;i<256;i++) {
	 		if((new_lut->tabLutR[i]-nb)<0)
	 			new_lut->tabLutR[i] = 0;
	 		else if((new_lut->tabLutR[i]-nb)>255)
	 			new_lut->tabLutR[i] = 255;
	 		else
	 			new_lut->tabLutR[i] = new_lut->tabLutR[i]-nb;
	 			
	 		if((new_lut->tabLutV[i]-nb)<0)
	 			new_lut->tabLutV[i] = 0;
	 		else if((new_lut->tabLutV[i]-nb)>255)
	 			new_lut->tabLutV[i] = 255;
	 		else
	 			new_lut->tabLutV[i] = new_lut->tabLutV[i]-nb;
	 			
	 		if((new_lut->tabLutB[i]-nb)<0)
	 			new_lut->tabLutB[i] = 0;
	 		else if((new_lut->tabLutB[i]-nb)>255)
	 			new_lut->tabLutB[i] = 255;
	 		else
	   			new_lut->tabLutB[i] = new_lut->tabLutB[i]-nb;
		}   
	}else {
		printf("Erreur d'allocation de la lut \n");
	}
}


// effets sur le contraste :
// le contraste joue sur une différence de luminescence
// Augmenter un contraste ou le diminuer c'est jouer entre 2 plages de luminescences
// en accentuant leur rapport




void addContraste(LLut* p_llut, int nb) {
	Lut *new_lut = malloc(sizeof *new_lut);

	if (new_lut != NULL) {
		
		addLUT(p_llut,new_lut);
		int i;
		
		for(i=0;i<256;i++) {

			if(new_lut->tabLutR[i] < 128) {
				// couche des rouges
				if((new_lut->tabLutR[i]-nb)>128)
					new_lut->tabLutR[i] = 128;
				else
					new_lut->tabLutR[i] = new_lut->tabLutR[i]-nb;
				
				// couche des verts
				if((new_lut->tabLutV[i]-nb)>128)
					new_lut->tabLutV[i] = 128;
				else
					new_lut->tabLutV[i] = new_lut->tabLutV[i]-nb;
				
				// couche des bleus
				if((new_lut->tabLutB[i]-nb)>128)
					new_lut->tabLutB[i] = 128;
				else
					new_lut->tabLutB[i] = new_lut->tabLutB[i]-nb;
			}
				
			else if (new_lut->tabLutR[i] >= 128) {
				// rouge
				if((new_lut->tabLutR[i]+nb)<128)
					new_lut->tabLutR[i] = 128;
				else
					new_lut->tabLutR[i] = new_lut->tabLutR[i]+nb;
				
				// vert	
				if((new_lut->tabLutV[i]+nb)<128)
					new_lut->tabLutV[i] = 128;
				else
					new_lut->tabLutV[i] = new_lut->tabLutV[i]+nb;
				
				// bleu	
				if((new_lut->tabLutB[i]+nb)<128)
					new_lut->tabLutB[i] = 128;
				else
					new_lut->tabLutB[i] = new_lut->tabLutB[i]+nb;
			}
		}
	}
	else {
		printf("Erreur d'allocation de la lut \n");
	}
}	

// pour diminuer le contrast on fait le processus inverse

void dimContraste(LLut* p_llut, int nb) {

	Lut *new_lut = malloc(sizeof *new_lut);

	if (new_lut != NULL) {
		
		addLUT(p_llut,new_lut);
		int i;

		for(i=0;i<256;i++) {

			if(new_lut->tabLutR[i] < 128) {
				if((new_lut->tabLutR[i]+nb)>128)
					new_lut->tabLutR[i] = 128;
				else
					new_lut->tabLutR[i] = new_lut->tabLutR[i]+nb;
					
				if((new_lut->tabLutV[i]+nb)>128)
					new_lut->tabLutV[i] = 128;
				else
					new_lut->tabLutV[i] = new_lut->tabLutV[i]+nb;
					
				if((new_lut->tabLutB[i]+nb)>128)
					new_lut->tabLutB[i] = 128;
				else
					new_lut->tabLutB[i] = new_lut->tabLutB[i]+nb;
			}
				
			else if (new_lut->tabLutR[i] >= 128) {
				if((new_lut->tabLutR[i]-nb)<128)
					new_lut->tabLutR[i] = 128;
				else
					new_lut->tabLutR[i] = new_lut->tabLutR[i]-nb;
					
				if((new_lut->tabLutV[i]-nb)<128)
					new_lut->tabLutV[i] = 128;
				else
					new_lut->tabLutV[i] = new_lut->tabLutV[i]-nb;
					
				if((new_lut->tabLutB[i]-nb)<128)
					new_lut->tabLutB[i] = 128;
				else
					new_lut->tabLutB[i] = new_lut->tabLutB[i]-nb;
			}
		}
	}
	else {
		printf("Erreur d'allocation de la lut \n");
	}
}

//couleur en négatifs, inversion des valeur des pixel par rapport à la 
//gamme de valeurs possible en RVB de 0 a 255
void invert(LLut* p_llut) {	
	Lut *new_lut = malloc(sizeof *new_lut);

	if (new_lut != NULL) {
		
		addLUT(p_llut,new_lut);
		int i;
	   	for (i=0; i<256; i++) {
	   		new_lut->tabLutR[i] = 255-new_lut->tabLutR[i];
	   		new_lut->tabLutV[i] = 255-new_lut->tabLutV[i];
	   		new_lut->tabLutB[i] = 255-new_lut->tabLutB[i];
	   	}
	}
	else {
		printf("Erreur d'allocation de la lut \n");
	}
} 	

/*Effet Sepia*/
// Effet noir et blanc
void B_W(Image* img) {
	
	int i;

	for (i=0; i<((img->heightImg)*(img->widthImg))*3; i+=3) {
		img->tabPixel[i] = (img->tabPixel[i] + img->tabPixel[i+1] + img->tabPixel[i+2])/3;
		img->tabPixel[i+1] = (img->tabPixel[i] + img->tabPixel[i+1] + img->tabPixel[i+2])/3;
		img->tabPixel[i+2] = (img->tabPixel[i] + img->tabPixel[i+1] + img->tabPixel[i+2])/3;
	}
}

//Colorisation
void colorize(LLut* p_llut, int R, int V, int B) {

	Lut *new_lut = malloc(sizeof *new_lut);

	if (new_lut != NULL) {
		
		addLUT(p_llut,new_lut);

		int i;
		for (i=0; i<256; i++) {

			if((new_lut->tabLutR[i]+R)<0)
	 			new_lut->tabLutR[i] = 0;
	 		else if((new_lut->tabLutR[i]+R)>255)
	 			new_lut->tabLutR[i] = 255;
	 		else
	 			new_lut->tabLutR[i] = new_lut->tabLutR[i]+R;
	 			
	 		if((new_lut->tabLutV[i]+V)<0)
	 			new_lut->tabLutV[i] = 0;
	 		else if((new_lut->tabLutV[i]+V)>255)
	 			new_lut->tabLutV[i] = 255;
	 		else
	 			new_lut->tabLutV[i] = new_lut->tabLutV[i]+V;
	 			
	 		if((new_lut->tabLutB[i]+B)<0)
	 			new_lut->tabLutB[i] = 0;
	 		else if((new_lut->tabLutB[i]+B)>255)
	 			new_lut->tabLutB[i] = 255;
	 		else
	   			new_lut->tabLutB[i] = new_lut->tabLutB[i]+B;
		}
	}
	else {
		printf("Erreur d'allocation de la lut \n");
	}
}

void sepia (LLut* p_llut, Image* img) {
	B_W(img);
	colorize(p_llut, 100, 50, 0);
}


/************** Déssallocation de la liste de lut **************/
void removeLLut(LLut* p_llut) {
	//Si la liste n'est pas vide
	if (p_llut->length != 0) {

		//Tant que la liste n'est pas vide
		while (p_llut->l_head != NULL) {

			Lut *lut_tmp = p_llut->l_head;
			p_llut->l_head = lut_tmp->l_next;
			free(lut_tmp);
		}
		
	}
	free(p_llut);
}
