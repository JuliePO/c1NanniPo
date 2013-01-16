#include <stdlib.h>
#include <stdio.h>
//Appel de la structure d'une lut
/*
#include "lut.h"
#include "image.h"

*/
//test en local
#include "../include/lut.h"
#include "../include/image.h"
#include "../include/calque.h"



/************* Création d'une nouvelle liste de lut *************/
LLUT* new_LLUT(void) {
	
	//Alloue de la mémoire 
	LLUT *p_lut = malloc(sizeof *p_lut);
	if (p_lut != NULL) {
		p_lut->length = 0;
		p_lut->l_head = NULL;
		p_lut->l_tail = NULL;
	}
	return p_lut;
}

/*********************************************************************/



//initialisation de la lut
int initLUT(LLUT* p_llut, LUT* new_lut) {

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







//application d'une LUT sur l'image
// il s'agit de remplacer les valeurs des pixels de l'image par celles de la lut
void applyLUT(Image* img, LUT* lut) {
	int i;
	for(i=0; i<((img->heightImg)*(img->widthImg)*3); i+=3){
		img->tabPixel[i]=(unsigned char)(lut->tabLutR[(int)img->tabPixel[i]]);
		img->tabPixel[i+1]=(unsigned char)(lut->tabLutV[(int)img->tabPixel[i+1]]);
		img->tabPixel[i+2]=(unsigned char)(lut->tabLutB[(int)img->tabPixel[i+2]]);
	}
}



/************* Supprimer une lut selon sa position *************/
LLUT* removeLut(LLUT* p_llut, int position) {

	// On vérifie si notre liste a été allouée
	if (p_llut != NULL) {

		//Verifie que que le lut existe
		if(p_llut->length >= position + 1) {

			//Vérifie s'il reste au moins un lut, si c'est le dernier lut alors ne le supprime pas
			if(p_llut->length > 1) {

				//Création d'un lut temporaire
				LUT *p_tmp = p_llut->l_head;

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
							LUT *p_temp = p_llut->l_head->l_next;
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
							LUT *p_temp = p_tmp->l_next;
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








/******Effets**********/


//luminosité
//il s'agit d'ajouté une valeur positive choisie aux valeurs des pixels
//pour gagner en luminosité

void addLum(LLUT* p_llut, int nb){

	LUT *new_lut = malloc(sizeof *new_lut);

	if (new_lut != NULL) {
		
		initLUT(p_llut,new_lut);

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
void dimLum(LLUT* p_llut, int nb){

	LUT *new_lut = malloc(sizeof *new_lut);

	if (new_lut != NULL) {
		
		initLUT(p_llut,new_lut);

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




void addContraste(LLUT* p_llut, int nb) {
	LUT *new_lut = malloc(sizeof *new_lut);

	if (new_lut != NULL) {
		
		initLUT(p_llut,new_lut);
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

void dimContraste(LLUT* p_llut, int nb) {

	LUT *new_lut = malloc(sizeof *new_lut);

	if (new_lut != NULL) {
		
		initLUT(p_llut,new_lut);
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
void invert(LLUT* p_llut) {	
	LUT *new_lut = malloc(sizeof *new_lut);

	if (new_lut != NULL) {
		
		initLUT(p_llut,new_lut);
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
void B_W(Image* img) {
	
	int i;

	for (i=0; i<((img->heightImg)*(img->widthImg))*3; i+=3) {
		img->tabPixel[i] = (img->tabPixel[i] + img->tabPixel[i+1] + img->tabPixel[i+2])/3;
		img->tabPixel[i+1] = (img->tabPixel[i] + img->tabPixel[i+1] + img->tabPixel[i+2])/3;
		img->tabPixel[i+2] = (img->tabPixel[i] + img->tabPixel[i+1] + img->tabPixel[i+2])/3;
	}
}

void colorize(LLUT* p_llut, int R, int V, int B) {

	LUT *new_lut = malloc(sizeof *new_lut);

	if (new_lut != NULL) {
		
		initLUT(p_llut,new_lut);

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

void sepia (LUT* lut, Image* img) {
	B_W(img);
	colorize(lut, 100, 50, 0);
}



int main(int argc, char const *argv[]) {

	printf("ça compile \n");
	return 0;
}
