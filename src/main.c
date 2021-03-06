/***************************************************************************
 *           2012_IMAC 1 Projet imagimp de Julie Po et Laetitia Nanni      *       
 ***************************************************************************/

#include <string.h>
#include <stdio.h>
#include <GL/glut.h>
#include "outils.h"
#include "interface.h"
#include "image.h"
#include "calque.h"
#include "historique.h"
#include "histogramme.h"
#include "ihm.h"
#include "lut.h"

/********** VARIABLE ***********/
#define EPSILON 0.0001;

/********** VARIABLES GLOBALES **********/

//Historique : liste
LHistorique historique;
LHistorique* ph = &historique;

LHistorique redo;
LHistorique* p_redo = &redo;

//Histogramme
Histogramme* histo;

//Calque : liste, calque courant et calque pour la suppression
LCalque calque;
LCalque* pc = &calque;

Calque* p_courant;
Calque* p_suppr;

//Image : première image, image finale et image du calque courant
Image image;
Image* p = &image;

Image image_final;
Image* pf = &image_final;

Image image_courant;
Image* pic = &image_courant;




/********** MAIN **********/
int main(int argc, char** argv) {

	glutGet(GLUT_ELAPSED_TIME); //Force à utiliser glutGet

	/****** VARIABLES ******/

	float opacity; //Pour récuperer l'opacite
	int mix; //Pour récuperer le mode d'operation
	int position; //Pour recuperer l'id
	int red, green, blue; //Pour recuperer le nombre de rouge, vert, blue pour remplir un calque d'une couleur unie
	int canal = 0; //Canal = 0 : global (1 : rouge, 2 : vert, 3 : bleu)
	int menu = 0; //Permet d'appliquer la fonction clickMouse en fonction du menu affiché: 1 = Menu Effets; 2 = Menu Calque; 3 = Menu Histogramme
	int switchCalque = 0; //  0 : image total && 1 : image du calque
	char adress[100]; //Adresse des images de calque
	char adressH[100]; //Adresse de l'histogramme
	char adressF[100]; //Adresse de l'image final
	float intensite; //Pour les modifications de luminosite et de contraste
	int r, v, b; //Pour la colorisation 

	/****** INITIALISATION DES ELEMENTS *****/

	//Initialisation de l'historique
	ph = initHistory();
	p_redo = initHistory();
	
	//Initialisation de la liste des calques
	pc = new_LCalque();

	//Calque courant
	p_courant = pc->p_head;

	//Chargement de la première image
	if(addCalqueImg(pc, 1, 0, argv[1]) == 0) {
		printf("Erreur : Probleme à l'ajout du premier calque\n");
		exit(1);
	}
	else {
		//Calque courant
		p_courant = pc->p_tail;
		//Ajout à l'historique
		addHistory(ph, p_courant, 0);
	}

	//Fusion des calques
	pf = fusionCalque(pc);

	/******* Application des lut s'il y en a qui sont passée en argument *********/
	void fristLut() {
		int i;

		//Vérifie le nombre d'arguments (vérifie si des luts doivent être appliquées)
		if(argc > 2) {

			for(i = 2; i < argc; i++) {
 
				if(strcmp(argv[i], "INVERT") == 0) {

					invert(p_courant->p_llut);
					//Ajout de l'action dans l'historique
					addHistory(ph, p_courant, 5);
					//Création d'un element de l'historique redo fantome (avec aucune action)
					addHistory(p_redo, p_courant, -2);

				}
				else if(strcmp(argv[i], "BW") == 0) {

					B_W(p_courant->image_src);
					addHistory(ph, p_courant, 4);

				}
				else if(strcmp(argv[i], "ADDLUM") == 0) {
					
					i++; //Augmente de un pour passer à l'argument suivant
					intensite = atoi(argv[i]);

					//Si la valeur n'est pas comprise entre 0 et 255 alors on redemande jusqu'à que c'est bon
					if(intensite < 0 || intensite > 255) {
						while(intensite < 0 || intensite > 255) {
							printf("Erreur entrez une valeur comprise entre 0 et 255 \n");
							printf("Entrez une valeur d'intensite :");
							scanf("%f", &intensite);
						}
					}

					addLum(p_courant->p_llut, intensite);
					//Ajout de l'action dans l'historique
					addHistory(ph, p_courant, 5);
					//Création d'un element de l'historique redo fantome (avec aucune action)
					addHistory(p_redo, p_courant, -2);
				}
				else if(strcmp(argv[i], "DIMLUM") == 0) {

					i++;  //Augmente de un pour passer à l'argument suivant
					intensite = atoi(argv[i]);

					//Si la valeur n'est pas comprise entre 0 et 255 alors on redemande jusqu'à que c'est bon
					if(intensite < 0 || intensite > 255) {
						while(intensite < 0 || intensite > 255) {
							printf("Erreur entrez une valeur comprise entre 0 et 255 \n");
							printf("Entrez une valeur d'intensite :");
							scanf("%f", &intensite);
						}
					}

					dimLum(p_courant->p_llut, intensite);
					//Ajout de l'action dans l'historique
					addHistory(ph, p_courant, 5);
					//Création d'un element de l'historique redo fantome (avec aucune action)
					addHistory(p_redo, p_courant, -2);
				}
				else if(strcmp(argv[i], "ADDCON") == 0) {
			
					i++;  //Augmente de un pour passer à l'argument suivant
					intensite = atoi(argv[i]);

					//Si la valeur n'est pas comprise entre 0 et 255 alors on redemande jusqu'à que c'est bon
					if(intensite < 0 || intensite > 255) {
						while(intensite < 0 || intensite > 255) {
							printf("Erreur entrez une valeur comprise entre 0 et 255 \n");
							printf("Entrez une valeur d'intensite :");
							scanf("%f", &intensite);
						}
					}

					addContraste(p_courant->p_llut, intensite);
					//Ajout de l'action dans l'historique
					addHistory(ph, p_courant, 5);
					//Création d'un element de l'historique redo fantome (avec aucune action)
					addHistory(p_redo, p_courant, -2);
				}
				else if(strcmp(argv[i], "DIMLUM") == 0) {

					i++;  //Augmente de un pour passer à l'argument suivant
					intensite = atoi(argv[i]);

					//Si la valeur n'est pas comprise entre 0 et 255 alors on redemande jusqu'à que c'est bon
					if(intensite < 0 || intensite > 255) {
						while(intensite < 0 || intensite > 255) {
							printf("Erreur entrez une valeur comprise entre 0 et 255 \n");
							printf("Entrez une valeur d'intensite :");
							scanf("%f", &intensite);
						}
					}

					dimContraste(p_courant->p_llut, intensite);
					//Ajout de l'action dans l'historique
					addHistory(ph, p_courant, 5);
					//Création d'un element de l'historique redo fantome (avec aucune action)
					addHistory(p_redo, p_courant, -2);
				}
				else if(strcmp(argv[i], "SEPIA") == 0) {

					sepia(p_courant->p_llut, p_courant->image_src);
					//Ajout de l'action dans l'historique
					addHistory(ph, p_courant, 5);
					//Création d'un element de l'historique redo fantome (avec aucune action)
					addHistory(p_redo, p_courant, -2);
				}
				else {
					printf("Erreur de lut\n Fin du programme\n");
					exit(1);
				}

			}
		}
	}

	/********* Affichage de l'histogramme *********/
	void afficheHisto() {
		//appel du menu principal
		drawMain();
		//appel du sous menu histogramme
		drawMenuHistogramme();

		int i=256, j;
		float value;

		//Fond blanc de l'histogramme
		fixeCouleur(0.8,0.8,0.8);
		drawCarre(0.64,0.38,0.98,0.87);

		//Battonnet noir/rouge/vert ou bleu pour afficher l'histogramme selon son canal d'écoute
		if (canal == 0)
			fixeCouleur(0,0,0);	
		else if (canal == 1)
			fixeCouleur(0.5,0.1,0.1);
		else if (canal == 2)
			fixeCouleur(0.1,0.5,0.1);
		else if (canal == 3)
			fixeCouleur(0.1,0.1,0.5);

		//Dessin un baton qui a la hauteur de la valeur en pourcentage 
		for(j=256; j>0; j--) {

			value =1-(((histo->values[j])*0.38/100.0)+0.24); //Met les valeurs en pourcentage
			//printf("%f\n",value );
			if (value > 0) { //on ne garde que ls valeurs positives
				drawLigne((((0.34*i)/255)+0.64),0.38,(((0.34*i)/255)+0.64),value);
				i--;
			}				
		}
	}
	/********* Action ajout d'un calque avec une image *********/
	void ACTIONaddCalqueImg() {
		//Recuperer l'adresse de l'image
		printf("\nEntrez l'adresse de l'image (images/votre_image.ppm) : ");
		scanf("%s", adress);

		//Recuperer l'opacite
		printf("Entrez l'opacite du calque (compris entre 0 et 1) : ");
		scanf("%f", &opacity);

		// Si l'opacite n'est pas compris entre 0 et 1 alors on redemande l'opacite jusqu'à que c'est bon
		if(opacity < 0 || opacity > 1) {

			while(opacity < 0 || opacity > 1) {
				printf("Erreur entrez une opacite comprise entre 0 et 1 \n");
				printf("Entrez l'opacite du calque : ");
				scanf("%f", &opacity);
			}
		}

		//Recuperer mode d'operation des calques
		printf("\nEntrez le mode de melange du calque ( 0 = Addition && 1 = Multiplication) :  ");
		scanf("%d", &mix); 

		// Si l'opacite est différent de 0 ou 1 alors on redemande le mode d'operation jusqu'à que c'est bon
		if(mix != 0 && mix != 1) {

			while(mix != 0 && mix != 1){
				printf("Erreur entrez 0 pour l'addition et 1 pour la multiplication \n");
				printf("\nEntrez le mode de melange du calque ( 0 = Addition && 1 = Multiplication) :  ");
				scanf("%d", &mix); 
			}
			
		}

		//Ajouter un calque avec l'image
		if(addCalqueImg(pc, opacity, mix, adress) == 0) {
			printf("Erreur : Probleme à l'ajout du premier calque\n");
		}
		//Le calque courant devient le calque qu'on vient d'ajouter
		p_courant = pc->p_tail;
		//Ajout de l'action dans l'historique
		addHistory(ph, p_courant, 0);
		addHistory(p_redo, p_courant, -1);
	}

	/********* Action d'ajouter un calque vide *********/
	void ACTIONaddCalqueVide() {
		//Recuperer l'opacite
		printf("\nEntrez l'opacite du calque (compris entre 0 et 1): ");
		scanf("%f", &opacity);

		// Si l'opacite n'est pas compris entre 0 et 1 alors on redemande l'opacite jusqu'à que c'est bon
		if(opacity < 0 || opacity > 1)  {

			while(opacity < 0 || opacity > 1) {
				printf("Erreur entrez une opacite comprise entre 0 et 1 \n");
				printf("Entrez l'opacite du calque : ");
				scanf("%f", &opacity);
			}
		}

		//Recuperer mode d'operation des calques
		printf("\nEntrez le mode de melange du calque ( 0 = Addition && 1 = Multiplication) :  ");
		scanf("%d", &mix); 

		// Si l'opacite est différent de 0 ou 1 alors on redemande le mode d'operation jusqu'à que c'est bon
		if(mix != 0 && mix != 1) {

			while(mix != 0 && mix != 1){
				printf("Erreur entrez 0 pour l'addition et 1 pour la multiplication \n");
				printf("\nEntrez le mode de melange du calque ( 0 = Addition && 1 = Multiplication) :  ");
				scanf("%d", &mix); 
			}
			
		}

		//Ajoute le calque
		addCalque(pc, opacity, mix);
		//Le calque courant devient le calque qu'on vient d'ajouter
		p_courant = pc->p_tail;
		//Ajout de l'action dans l'historique
		addHistory(ph, p_courant, 0);
		addHistory(p_redo, p_courant, -2);
	}

	/********* Action de supprimer le calque courant *********/
	void ACTIONdelCurrentLayer(){
		//Ajout de l'action dans l'historique
		addHistory(ph, p_courant, 1);

		//pointeur suppr = pointeur calque courant pour pouvoir changer de calque courant avant de supprimer le calque
		p_suppr = p_courant;

		//S'il reste plus d'un calque
		if(pc->length > 1) {
			//Si c'est le premier calque alors le calque courant devient le calque suivant
			if(p_courant->p_prev == NULL) {
				p_courant = p_courant->p_next;
			}
			//Sinon le calque courant devient le calque précédent
			else {
				p_courant = p_courant->p_prev;
				printf("ID calque courant : %d \n", p_courant->id);
			}
			//Supprime le calque
			removeCalque(pc, p_suppr);
			printf("Le calque a bien été supprimé\n");
		}
		else
			printf("Il reste un seul calque, impossible de le supprimer");
	}

	/********* Action de sauvegarde de l'image finale *********/
	void ACTIONsaveImg(){
		//Recuperer l'adresse de l'image finale
		printf("\nEntrez l'adresse de l'image (images/votre_image.ppm) : ");
		scanf("%s", adressF);

		//Si la sauvegarde a été faite alors affiche l'adresse
		if(saveImg(pf, adressF) == 1)
			printf("L'image a bien ete enregistree dans %s\n", adressF);
		else
			printf("Ereur dans la sauvegarde de l'image\n");
	}

	/********* Action de remplissage du calque courant *********/
	void ACTIONlayerColor(){
		//Récupère la valeur de rouge
		printf("\nEntrez la valeur rouge (comprise entre 0 et 255) :");
		scanf("%d", &red);

		//Si la valeur n'est pas comprise entre 0 et 255 alors on redemande jusqu'à que c'est bon
		if(red < 0 || red > 255) {
			while(red < 0 || red > 255) {
				printf("Erreur entrez une valeur comprise entre 0 et 255 \n");
				printf("Entrez la valeur rouge :");
				scanf("%d", &red);
			}
		}

		//Récupère la valeur de vert
		printf("Entrez la valeur vert (comprise entre 0 et 255) :");
		scanf("%d", &green);

		//Si la valeur n'est pas comprise entre 0 et 255 alors on redemande jusqu'à que c'est bon
		if(green < 0 || green > 255) {
			while(green < 0 || green > 255) {
				printf("Erreur entrez une valeur comprise entre 0 et 255 \n");
				printf("Entrez la valeur rouge :");
				scanf("%d", &green);
			}
		}

		//Récupère la valeur de bleu
		printf("Entrez la valeur blue (comprise entre 0 et 255) :");
		scanf("%d", &blue);

		//Si la valeur n'est pas comprise entre 0 et 255 alors on redemande jusqu'à que c'est bon
		if(blue < 0 || blue > 255) {
			while(blue < 0 || blue > 255) {
				printf("Erreur entrez une valeur comprise entre 0 et 255 \n");
				printf("Entrez la valeur rouge :");
				scanf("%d", &blue);
			}
		}

		//Rempli le calque par la couleur
		remplirCalque(p_courant, red, green, blue);
		//Ajout de l'action dans l'historique
		addHistory(ph, p_courant, 4);
	}

	/********* Action d'actualisation d'image et d'histogramme *********/
	void ACTIONActualisation() {

		//Si switchCalque = 0 (mode image final)
		if(switchCalque == 0) {
			pf = fusionCalque(pc); //Fusion des calques
			histo = createHistogramme(pf, canal); //Redefinition de l'histogramme
			actualiseImage(pf->tabPixel); //Actualiser l'image
		}
		//Sinon (mode calque courant)
		else {
			calqueCourant(p_courant, pic); //Application des effets sur le calque courant
			histo = createHistogramme(pic, canal); //Redefinition de l'histogramme
			actualiseImage(pic->tabPixel); //Actualiset l'image
		}

	}
	/********** Action de colorisation de l'image *****************/
	void ACTIONimgColor(){
		printf("Entrez une valeur de rouge (entre 0 et 255) : ");
		scanf("%d", &r);

		//Si la valeur n'est pas comprise entre 0 et 255 alors on redemande jusqu'à que c'est bon
		if(r < 0 || r > 255) {
			while(r < 0 || r > 255) {
				printf("Erreur entrez une valeur comprise entre 0 et 255 \n");
				printf("Entrez une valeur de rouge :");
				scanf("%d", &r);
			}
		}

		printf("Entrez une valeur de vert (entre 0 et 255) : ");
		scanf("%d", &v);

		//Si la valeur n'est pas comprise entre 0 et 255 alors on redemande jusqu'à que c'est bon
		if(v < 0 || v > 255) {
			while(v < 0 || v > 255) {
				printf("Erreur entrez une valeur comprise entre 0 et 255 \n");
				printf("Entrez une valeur de vert :");
				scanf("%d", &v);
			}
		}

		printf("Entrez une valeur de bleu (entre 0 et 255) : ");
		scanf("%d", &b);

		//Si la valeur n'est pas comprise entre 0 et 255 alors on redemande jusqu'à que c'est bon
		if(b < 0 || b > 255) {
			while(b < 0 || b > 255) {
				printf("Erreur entrez une valeur comprise entre 0 et 255 \n");
				printf("Entrez une valeur de bleu :");
				scanf("%d", &b);
			}
		}

		colorize(p_courant->p_llut, r, v, b);
		//Ajout de l'action dans l'historique
		addHistory(ph, p_courant, 5);
		//Création d'un element de l'historique redo fantome (avec aucune action)
		addHistory(p_redo, p_courant, -2);
	}
	/****** GESTION TOUCHES CLAVIER ******/
	void kbdFunc(unsigned char c, int x, int y) {
	
		switch(c) {

			/******** CALQUES ******/

			//Touche W : Afficher l'id du calque courant
			case 'W' :
				printf("\nID du calque courant : %d\n", p_courant->id);
				break;

			//Touche n : Naviger dans la liste de calque
			case 'n' : 
				printf("\nEntrez l'id du calque :");
				scanf("%d", &position);

				//Le calque courant devient le calque qui a l'id entré par l'utilisateur
				p_courant = navCalque (pc, p_courant, position);
				//Afficher l'id du calque courant
				printf("ID du calque courant : %d \n", p_courant->id);
				break;

			//Touche w : Changer le mode de vue : 0 = Image final et 1 = calque courant
			case 'w' :
				//Si le mode de vu est en mode image final alors il change en mode calque courant
				if(switchCalque == 0) {
					switchCalque = 1;
					printf("Calque courant : %d\n", p_courant->id);
				}
				//Sinon ça veut dire que le mode de vue est en mode calque courant donc change en mode image final
				else {
					switchCalque = 0;
					printf("Image final\n");
				}
				break;

			//Touche a : Afficher la liste de calque
			case 'a' :
				afficheLCalque(pc);
				break;

			//Touche N : Ajouter un nouveau calque vide
			case 'N' :
				ACTIONaddCalqueVide();
				break;

			//Touche I : Ajouter un calque avec une image
			case 'I' :	
				ACTIONaddCalqueImg();
				break;

			//Touche R : Supprimer le calque courant
			case 'R' :
				ACTIONdelCurrentLayer();
				break;

			//Touche S : Sauvegarde de l'image final
			case 'S' :
				ACTIONsaveImg();
				break;

			//Touche o : Modifier l'opacite du calque
			case 'o' : 
			
				//Recuperer l'opacite
				printf("\nEntrez l'opacite du calque (compris entre 0 et 1) : ");
				scanf("%f", &opacity);

				// Si l'opacite n'est pas compris entre 0 et 1 alors on redemande l'opacite jusqu'à que c'est bon
				if(opacity < 0 || opacity > 1) {
					while(opacity < 0 || opacity > 1) {
						printf("Erreur entrez une opacite comprise entre 0 et 1 \n");
						printf("Entrez l'opacite du calque : ");
						scanf("%f", &opacity);
					}
				}
			
				//Modifie l'opacite
				modifOpacity(p_courant, opacity);
				//Ajout de l'action dans l'historique
				addHistory(ph, p_courant, 2);
				break;

			//Touche m : Modifier le mode d'operation
			case 'm' :
				//Recuperer mode d'operation des calques
				printf("\nEntrez le mode de melange du calque ( 0 = Addition && 1 = Multiplication) :  ");
				scanf("%d", &mix); 

				// Si l'opacite est différent de 0 ou 1 alors on redemande le mode d'operation jusqu'à que c'est bon
				if(mix != 0 && mix != 1) {
					while(mix != 0 && mix != 1){
						printf("Erreur entrez 0 pour l'addition et 1 pour la multiplication \n");
						printf("\nEntrez le mode de melange du calque ( 0 = Addition && 1 = Multiplication) :  ");
						scanf("%d", &mix); 
					}
					
				}
				//Modification du mode d'operation du calque
				modifMix(p_courant, mix);
				//Ajout de l'action dans l'historique
				addHistory(ph, p_courant, 3);
				break;

			//Touche G : Remplir le calque d'une couleur unie
			case 'G' :
				ACTIONlayerColor();
				break;

			/******** HISTORIQUE ******/

			//Touche h : Afficher l'historique
			case 'h' :
				AfficheHistory(ph);
				break;
			//Touche z : Annuler la derniere action
			case 'z' :
				//Annule la derniere action
				cancelHistory(ph, pc, p_redo);
				break;
			//Touche Z : Redo
			case 'Z' : 
				redoHistory (p_redo, pc, ph);
				break;

			//Touche H : Affiche Historique redo
			case 'H' :
				AfficheHistory(p_redo);
				printf("taille : %d\n\n", p_redo->length);
				break;

			/******** HISTOGRAMME ******/
				
			//Touche t : Afficher l'histogramme
			case 't' : 
				fixeFonctionDessin(afficheHisto);
				break;


			//Touche x : Changement de canal d'écoute pour l'histogramme
			case 'x' :
				//Le canal avant changement
				printf("Canal : %d", canal);
				//Récupère le nouveau canal
				printf("Entrez le nouveau canal (0 : global, 1 : rouge, 2 : vert, 3 : bleu) : ");
				scanf("%d", &canal);

				//Si le canal n'est pas 0, 1, 2 ou 3 alors on redemande jusqu'à que c'est bon
				if(canal != 0 && canal != 1 && canal != 2 && canal != 3) {

					while(canal != 0 && canal != 1 && canal != 2 && canal != 3) {
						printf("Erreur entrez une valeur (0 : global, 1 : rouge, 2 : vert, 3 : bleu)\n");
						printf("Entrez le canal :");
						scanf("%d", &canal);
					}
				}
				break;

			//Touche T : Sauvegarde de l'histogramme en image ppm
			case 'T' : 
				//Récupere l'adresse de l'image
				printf("\nEntrez l'adresse de l'image (images/votre_image.ppm) : ");
				scanf("%s", adressH);			
				//Sauvegarde de l'histogramme
				SaveHisto(histo, adressH);
				break;

			/******** EFFETS : LUT ******/

			//Touche A : Afficher la liste de luts du calque courant
			case 'A' :
				afficheLLut(p_courant->p_llut);
				break;

			//Touche L : Ajout de luminosite
			case 'L' : 
				printf("Entrez un entier pour une valeur d'intensite (entre 0 et 255) : ");
				scanf("%f", &intensite);

				//Si la valeur n'est pas comprise entre 0 et 255 alors on redemande jusqu'à que c'est bon
				if(intensite < 0 || intensite > 255) {
					while(intensite < 0 || intensite > 255) {
						printf("Erreur entrez une valeur comprise entre 0 et 255 \n");
						printf("Entrez une valeur d'intensite :");
						scanf("%f", &intensite);
					}
				}

				addLum(p_courant->p_llut, intensite);
				//Ajout de l'action dans l'historique
				addHistory(ph, p_courant, 5);
				//Création d'un element de l'historique redo fantome (avec aucune action)
				addHistory(p_redo, p_courant, -2);

				break;
			//Touche l : Diminution de la luminosite
			case 'l' :
				printf("Entrez un entier pour une valeur d'intensite (entre 0 et 255) : ");
				scanf("%f", &intensite);

				//Si la valeur n'est pas comprise entre 0 et 255 alors on redemande jusqu'à que c'est bon
				if(intensite < 0 || intensite > 255) {
					while(intensite < 0 || intensite > 255) {
						printf("Erreur entrez une valeur comprise entre 0 et 255 \n");
						printf("Entrez une valeur d'intensite :");
						scanf("%f", &intensite);
					}
				}

				dimLum(p_courant->p_llut, intensite);
				//Ajout de l'action dans l'historique
				addHistory(ph, p_courant, 5);
				//Création d'un element de l'historique redo fantome (avec aucune action)
				addHistory(p_redo, p_courant, -2);

				break; 

			//Touche C : Ajout de contraste
			case 'C' :
				printf("Entrez un entier pour une valeur d'intensite (entre 0 et 255) : ");
				scanf("%f", &intensite);

				//Si la valeur n'est pas comprise entre 0 et 255 alors on redemande jusqu'à que c'est bon
				if(intensite < 0 || intensite > 255) {
					while(intensite < 0 || intensite > 255) {
						printf("Erreur entrez une valeur comprise entre 0 et 255 \n");
						printf("Entrez une valeur d'intensite :");
						scanf("%f", &intensite);
					}
				}

				addContraste(p_courant->p_llut, intensite);
				//Ajout de l'action dans l'historique
				addHistory(ph, p_courant, 5);
				//Création d'un element de l'historique redo fantome (avec aucune action)
				addHistory(p_redo, p_courant, -2);

				break;

			//Touche c : Diminution du contraste
			case 'c' :
				printf("Entrez un entier pour une valeur d'intensite (entre 0 et 255) : ");
				scanf("%f", &intensite);
					
				//Si la valeur n'est pas comprise entre 0 et 255 alors on redemande jusqu'à que c'est bon
				if(intensite < 0 || intensite > 255) {
					while(intensite < 0 || intensite > 255) {
						printf("Erreur entrez une valeur comprise entre 0 et 255 \n");
						printf("Entrez une valeur d'intensite :");
						scanf("%f", &intensite);
					}
				}

				dimContraste(p_courant->p_llut, intensite);
				//Ajout de l'action dans l'historique
				addHistory(ph, p_courant, 5);
				//Création d'un element de l'historique redo fantome (avec aucune action)
				addHistory(p_redo, p_courant, -2);

				break;

			//Touche v : Inversion des couleurs
			case 'v' :
				invert(p_courant->p_llut);
				//Ajout de l'action dans l'historique
				addHistory(ph, p_courant, 5);
				//Création d'un element de l'historique redo fantome (avec aucune action)
				addHistory(p_redo, p_courant, -2);
				break;

			//Touche b : Passage de l'image en noir et blanc
			case 'b' :
				B_W(p_courant->image_src);
				//Ajout de l'action dans l'historique
				addHistory(ph, p_courant, 4);
				break;

			//Touche g : Colorisation de l'image
			case 'g' : 
				ACTIONimgColor();
				break;

			//Touche s : Sepia
			case 's' :
				sepia(p_courant->p_llut, p_courant->image_src);
				//Ajout de l'action dans l'historique
				addHistory(ph, p_courant, 5);
				//Création d'un element de l'historique redo fantome (avec aucune action)
				addHistory(p_redo, p_courant, -2);
				break;

			//Touche r : Supprimer la derniere lut
			case 'r' :
				p_courant->p_llut = removeLut(p_courant->p_llut, p_courant->p_llut->l_tail->id);
				recupImg(ph, p_courant);
				addHistory(ph, p_courant, 6);
				break;

			//Touche Escape : fin du programme
			case 27 :
				printf("Fin du programme\n");
				
				//Supprimer les elements 
				removeAll(p, pf, pic, pc, ph, p_redo, histo);

				//Fin du programme
				exit(0);
				break;

			//Les autres touches
			default :
				printf("Touche non attribuer\n");
		}
		
		//Actualisation de l'image
		ACTIONActualisation();

	}

	/****** GESTION TOUCHES CLAVIER SPECIALE ******/
	void kbdSpFunc(int c, int x, int y) {
	
		switch(c) {
			//Touche F1 : Afficher l'aide
			case GLUT_KEY_F1 :
				help();
				break;

			//Touche FLECHE BAS : Aller sur le calque précédent
			case GLUT_KEY_DOWN :
				//Si c'est le premier calque
				if(p_courant->p_prev == NULL)
					printf("Premier calque, impossible d'aller plus loin\n");
				else {
					p_courant = p_courant->p_prev; //Le calque courant devient le calque précédent
					printf("ID calque courant : %d \n", p_courant->id);
				}
				break;

			//Touche FLECHE HAUT : Aller sur le calque suivant
			case GLUT_KEY_UP :

				//Si c'est le dernier calque
				if(p_courant->p_next == NULL)
					printf("Dernier calque, impossible d'aller plus loin\n");
				else {
					p_courant = p_courant->p_next; //Le calque courant devient le calque suivant
					printf("ID calque courant : %d \n", p_courant->id);
				}
				break;

			//Touche FLECHE DE GAUCHE : Diminuer l'opacite du calque
			case GLUT_KEY_LEFT :
				//Si l'opacite est à 0 (minimum)
				if(p_courant->opacity <= 0)
					printf("Opacite est dejà à 0\n");
				else {
					p_courant->opacity -= 0.1; //Diminuer de 0.1 l'opacite de calque
					printf("Opacite : %f\n", p_courant->opacity);
					//Ajout de l'action dans l'historique
					addHistory(ph, p_courant, 2);
				}
				break;

			//Touche FLECHE DE DROITE : Augmente l'opacite du calque
			case GLUT_KEY_RIGHT :
				//Si l'opacite est à 1 (maximum)
				if(p_courant->opacity >= 1)
					printf("Opacite est dejà à 100\n");
				else {
					p_courant->opacity += 0.1; //Augmente de 0.1 l'opacite de calque
					printf("Opacite : %f\n", p_courant->opacity); 
					//Ajout de l'action dans l'historique
					addHistory(ph, p_courant, 2);
				}
				break;

			//Les autres touches
			default :
				printf("Touche non attribuer\n");
		}

		//Actualisation de l'image
		ACTIONActualisation();

	}

	/* GESTION CLICKS SOURIS = BOUTONS*/
	void clickMouse(int button,int state,int x,int y) {
		int widthWin = pf->widthImg + 300; //= 512
		int heightWin = pf->heightImg + 60;
		// button ajout de calque
		if (button == GLUT_LEFT_BUTTON) {
			if(state == GLUT_DOWN) {

				/*****header : Menu principal ****/

				// bouton quitter 
				if (x > (widthWin*0.02)  && x < (widthWin*0.05) && y > (heightWin-(heightWin*0.97)) && y < (heightWin-(heightWin*0.92)) ) {
					printf("Fin du programme\n");
					//Supprimer les elements 
					removeAll(p, pf, pic, pc, ph, p_redo, histo);
					//Fin du programme
					exit(0);
				}
				// bt sauver
				if (x > (widthWin*0.07)  && x < (widthWin*0.16) && y > (heightWin-(heightWin*0.97)) && y < (heightWin-(heightWin*0.92)) ) {
					ACTIONsaveImg();

				}

				/***Gestion de l'historique**/
				// bt Undo
				if (x > (widthWin*0.185)  && x < (widthWin*0.27) && y > (heightWin-(heightWin*0.97)) && y < (heightWin-(heightWin*0.92)) ) {
					cancelHistory(ph, pc, p_redo);
					ACTIONActualisation();

				}
				// bt Afficher l'historique
				if (x > (widthWin*0.27)  && x < (widthWin*0.39) && y > (heightWin-(heightWin*0.97)) && y < (heightWin-(heightWin*0.92)) ) {
					AfficheHistory(ph);

				}
				// bt Redo
				if (x > (widthWin*0.39)  && x < (widthWin*0.47) && y > (heightWin-(heightWin*0.97)) && y < (heightWin-(heightWin*0.92)) ) {
					redoHistory (p_redo, pc, ph);
					ACTIONActualisation();

				}

				/***Switch image courante/finale***/
				// bt img courante
				if (x > (widthWin*0.49)  && x < (widthWin*0.63) && y > (heightWin-(heightWin*0.97)) && y < (heightWin-(heightWin*0.92)) ) {
					if(switchCalque == 0) {
						switchCalque = 1;
						fixeFonctionDessin(drawSwitchF);
					}
					//Sinon ça veut dire que le mode de vue est en mode calque courant donc change en mode image final
					else {
						switchCalque = 0;
						fixeFonctionDessin(drawMain);
					}					
					ACTIONActualisation();
				}

				// bt img finale

				/***menu principal***/
				// bt menu lut
				if (x > (widthWin*0.65)  && x < (widthWin*0.75) && y > (heightWin-(heightWin*0.97)) && y < (heightWin-(heightWin*0.92)) ) {
					fixeFonctionDessin(drawMenuLut);
					menu=1;

				}
				// bt menu calque (si image = image.ppm)
				if (x > (widthWin*0.75)  && x < (widthWin*0.85) && y > (heightWin-(heightWin*0.97)) && y < (heightWin-(heightWin*0.92)) ) {
					fixeFonctionDessin(drawMenuLayer);
					menu=2;

				}
				// bt menu histogramme
				if (x > (widthWin*0.86)  && x < (widthWin*0.975) && y > (heightWin-(heightWin*0.97)) && y < (heightWin-(heightWin*0.92)) ) {
					fixeFonctionDessin(afficheHisto);
					menu=3;
				}

				/******** Sous menu lut *************/


				if (menu == 1) {

					// bt + contraste
					if (x > (widthWin*0.74)  && x < (widthWin*0.96) && y > (heightWin-(heightWin*0.85)) && y < (heightWin-(heightWin*0.80)) ) {
						printf("Entrez un entier pour une valeur d'intensite (entre 0 et 255) : ");
						scanf("%f", &intensite);

						//Si la valeur n'est pas comprise entre 0 et 255 alors on redemande jusqu'à que c'est bon
						if(intensite < 0 || intensite > 255) {
							while(intensite < 0 || intensite > 255) {
								printf("Erreur entrez une valeur comprise entre 0 et 255 \n");
								printf("Entrez une valeur d'intensite :");
								scanf("%f", &intensite);
							}
						}

						addContraste(p_courant->p_llut, intensite);
						//Ajout de l'action dans l'historique
						addHistory(ph, p_courant, 5);
						//Création d'un element de l'historique redo fantome (avec aucune action)
						addHistory(p_redo, p_courant, -2);

						//Actualisation de l'image					
						ACTIONActualisation();
					}
					

					// [ bt - Contraste ]

					if (x > (widthWin*0.74)  && x < (widthWin*0.96) && y > (heightWin-(heightWin*0.80)) && y < (heightWin-(heightWin*0.75)) ) {
						printf("Entrez un entier pour une valeur d'intensite (entre 0 et 255) : ");
						scanf("%f", &intensite);
							
						//Si la valeur n'est pas comprise entre 0 et 255 alors on redemande jusqu'à que c'est bon
						if(intensite < 0 || intensite > 255) {
							while(intensite < 0 || intensite > 255) {
								printf("Erreur entrez une valeur comprise entre 0 et 255 \n");
								printf("Entrez une valeur d'intensite :");
								scanf("%f", &intensite);
							}
						}

						dimContraste(p_courant->p_llut, intensite);
						//Ajout de l'action dans l'historique
						addHistory(ph, p_courant, 5);
						//Création d'un element de l'historique redo fantome (avec aucune action)
						addHistory(p_redo, p_courant, -2);

						// Actualisation de l'image
						ACTIONActualisation();

					}


					// [ bt + Luminosité ]

					if (x > (widthWin*0.74)  && x < (widthWin*0.96) && y > (heightWin-(heightWin*0.75)) && y < (heightWin-(heightWin*0.70)) ) {
						printf("luminosité1 %d\n", menu);
						printf("Entrez un entier pour une valeur d'intensite (entre 0 et 255) : ");
						scanf("%f", &intensite);

						//Si la valeur n'est pas comprise entre 0 et 255 alors on redemande jusqu'à que c'est bon
						if(intensite < 0 || intensite > 255) {
							while(intensite < 0 || intensite > 255) {
								printf("Erreur entrez une valeur comprise entre 0 et 255 \n");
								printf("Entrez une valeur d'intensite :");
								scanf("%f", &intensite);
							}
						}

						addLum(p_courant->p_llut, intensite);
						//Ajout de l'action dans l'historique
						addHistory(ph, p_courant, 5);
						//Création d'un element de l'historique redo fantome (avec aucune action)
						addHistory(p_redo, p_courant, -2);

						//Actualisation de l'image
						ACTIONActualisation();
					}


					// [ bt - luminosité ]

					if (x > (widthWin*0.74)  && x < (widthWin*0.96) && y > (heightWin-(heightWin*0.70)) && y < (heightWin-(heightWin*0.65)) ) {
						printf("Entrez un entier pour une valeur d'intensite (entre 0 et 255) : ");
						scanf("%f", &intensite);

						//Si la valeur n'est pas comprise entre 0 et 255 alors on redemande jusqu'à que c'est bon
						if(intensite < 0 || intensite > 255) {
							while(intensite < 0 || intensite > 255) {
								printf("Erreur entrez une valeur comprise entre 0 et 255 \n");
								printf("Entrez une valeur d'intensite :");
								scanf("%f", &intensite);
							}
						}

						dimLum(p_courant->p_llut, intensite);
						//Ajout de l'action dans l'historique
						addHistory(ph, p_courant, 5);
						//Création d'un element de l'historique redo fantome (avec aucune action)
						addHistory(p_redo, p_courant, -2);

						//Actualiser l'image
						ACTIONActualisation();
					}



					// [ bt Négatif couleurs ]

					if (x > (widthWin*0.74)  && x < (widthWin*0.96) && y > (heightWin-(heightWin*0.65)) && y < (heightWin-(heightWin*0.60)) ) {
						invert(p_courant->p_llut);
						//Ajout de l'action dans l'historique
						addHistory(ph, p_courant, 5);
						//Création d'un element de l'historique redo fantome (avec aucune action)
						addHistory(p_redo, p_courant, -2);					
						//Actualisation img
						ACTIONActualisation();
					}


					// [ bt Sepia ]

					if (x > (widthWin*0.74)  && x < (widthWin*0.96) && y > (heightWin-(heightWin*0.60)) && y < (heightWin-(heightWin*0.55)) ) {
						sepia(p_courant->p_llut, p_courant->image_src);
						//Ajout de l'action dans l'historique
						addHistory(ph, p_courant, 5);
						//Création d'un element de l'historique redo fantome (avec aucune action)
						addHistory(p_redo, p_courant, -2);					
						//actualisation img
						ACTIONActualisation();
					}


					// [ bt Noir et blanc ]

					if (x > (widthWin*0.74)  && x < (widthWin*0.96) && y > (heightWin-(heightWin*0.55)) && y < (heightWin-(heightWin*0.50)) ) {
						B_W(p_courant->image_src);
						//Ajout de l'action dans l'historique
						addHistory(ph, p_courant, 4);		
						//Actualisation img
						ACTIONActualisation();			
					}


					// [ bt Colorisation  ]

					if (x > (widthWin*0.74)  && x < (widthWin*0.96) && y > (heightWin-(heightWin*0.50)) && y < (heightWin-(heightWin*0.45)) ) {
						//appel de la fonction de colorisation
						ACTIONimgColor();
						//actualisation de l'image
						ACTIONActualisation();
					}


					// [ bt Voir tous les effets appliques  ]

					if (x > (widthWin*0.65)  && x < (widthWin*0.96) && y > (heightWin-(heightWin*0.42)) && y < (heightWin-(heightWin*0.37)) ) {
						afficheLLut(p_courant->p_llut);
						//actualisation img
						ACTIONActualisation();
					}


					// [ bt supprimer dernier effet appliqué  ]

					if (x > (widthWin*0.65)  && x < (widthWin*0.96) && y > (heightWin-(heightWin*0.37)) && y < (heightWin-(heightWin*0.32)) ) {
						p_courant->p_llut = removeLut(p_courant->p_llut, p_courant->p_llut->l_tail->id);
						recupImg(ph, p_courant);
						addHistory(ph, p_courant, 6);	
						//actualisation de l'image
						ACTIONActualisation();
					}
				}


				/******** Sous menu calque *************/

				if (menu == 2) {
					// navigation calque précédent
					if (x > (widthWin*0.74)  && x < (widthWin*0.84) && y > (heightWin-(heightWin*0.85)) && y < (heightWin-(heightWin*0.80)) ) {
						if(p_courant->p_prev == NULL)
							printf("Premier calque, impossible d'aller plus loin\n");
						else {
							p_courant = p_courant->p_prev; //Le calque courant devient le calque précédent
							printf("ID calque courant : %d \n", p_courant->id);
							//Actualisation de l'image
							ACTIONActualisation();
						}
					}			
					// navigation calque suivant
					if (x > (widthWin*0.86)  && x < (widthWin*0.96) && y > (heightWin-(heightWin*0.85)) && y < (heightWin-(heightWin*0.80)) ) {
						//Si c'est le dernier calque
						if(p_courant->p_next == NULL)
							printf("Dernier calque, impossible d'aller plus loin\n");
						else {
							p_courant = p_courant->p_next; //Le calque courant devient le calque suivant
							printf("ID calque courant : %d \n", p_courant->id);
							//Actualisation de l'image
							ACTIONActualisation();
						}					
					}
					//bt Ajout de calque avec sans image
					if (x > (widthWin*0.74)  && x < (widthWin*0.96) && y > (heightWin-(heightWin*0.79)) && y < (heightWin-(heightWin*0.74)) ) {
						ACTIONaddCalqueImg();
						//Actualisation de l'image
						ACTIONActualisation();
					}
					//bt Ajout de calque avec une Image	
					if (x > (widthWin*0.74)  && x < (widthWin*0.96) && y > (heightWin-(heightWin*0.74)) && y < (heightWin-(heightWin*0.69)) ) {
						ACTIONaddCalqueVide();
						//Actualisation de l'image
						ACTIONActualisation();
					}
					//bt Suppression du calque courrent
					if (x > (widthWin*0.74)  && x < (widthWin*0.96) && y > (heightWin-(heightWin*0.69)) && y < (heightWin-(heightWin*0.64)) ) {
						ACTIONdelCurrentLayer();
						//Actualisation de l'image
						ACTIONActualisation();
					}
					//bt modification de l'opacité
					//diminution (bt -)
					if (x > (widthWin*0.74)  && x < (widthWin*0.78) && y > (heightWin-(heightWin*0.60)) && y < (heightWin-(heightWin*0.55)) ) {
						//Si l'opacite est à 0 (minimum)
						if(p_courant->opacity <= 0)
							printf("Opacite est dejà à 0\n");
						else {
							p_courant->opacity -= 0.1; //Diminuer de 0.1 l'opacite de calque
							printf("Opacite : %f\n", p_courant->opacity);
							//Actualisation de l'image
							ACTIONActualisation();
						}
						//Ajout de l'action dans l'historique
						addHistory(ph, p_courant, 2);				
					}
					// ajout d'opacité (bt +)
					if (x > (widthWin*0.92)  && x < (widthWin*0.96) && y > (heightWin-(heightWin*0.60)) && y < (heightWin-(heightWin*0.55)) ) {
						//Si l'opacite est à 1 (maximum)
						if(p_courant->opacity >= 1)
							printf("Opacite est dejà à 100\n");
						else {
							p_courant->opacity += 0.1; //Augmente de 0.1 l'opacite de calque
							printf("Opacite : %f\n", p_courant->opacity);
							//Actualisation de l'image
							ACTIONActualisation(); 
						}
						//Ajout de l'action dans l'historique
						addHistory(ph, p_courant, 2);
					}
					//remplir le calque d'une couleur unie
					if (x > (widthWin*0.74)  && x < (widthWin*0.96) && y > (heightWin-(heightWin*0.54)) && y < (heightWin-(heightWin*0.49)) ) {
						ACTIONlayerColor();
						//Actualisation de l'image
						ACTIONActualisation();
					}
					// changer le mode d'opération du calque
					// addition 0
					if (x > (widthWin*0.74)  && x < (widthWin*0.78) && y > (heightWin-(heightWin*0.48)) && y < (heightWin-(heightWin*0.43)) ) {
						mix = 0;
						//Modification du mode d'operation du calque
						modifMix(p_courant, mix);
						//Ajout de l'action dans l'historique
						addHistory(ph, p_courant, 3);
						//Actualisation de l'image
						ACTIONActualisation();
					}
					// multiplication 1
					if (x > (widthWin*0.92)  && x < (widthWin*0.96) && y > (heightWin-(heightWin*0.48)) && y < (heightWin-(heightWin*0.43)) ) {
						mix = 1;
						//Modification du mode d'operation du calque
						modifMix(p_courant, mix);
						//Ajout de l'action dans l'historique
						addHistory(ph, p_courant, 3);	
						//Actualisation de l'image
						ACTIONActualisation();				
					}
				}

				/******* Sous menu de l'historique******/

				if(menu == 3) {

					//bit changer de cannal:
					//global
					if (x > (widthWin*0.75)  && x < (widthWin*0.84) && y > (heightWin-(heightWin*0.36)) && y < (heightWin-(heightWin*0.31)) ) {
						canal = 0;
						//actualisation de l'image
						ACTIONActualisation();
					}
					//R
					if (x > (widthWin*0.75)  && x < (widthWin*0.84) && y > (heightWin-(heightWin*0.31)) && y < (heightWin-(heightWin*0.26)) ) {
						canal = 1;
						ACTIONActualisation();
					}
					//V
					if (x > (widthWin*0.75)  && x < (widthWin*0.84) && y > (heightWin-(heightWin*0.26)) && y < (heightWin-(heightWin*0.21)) ) {
						canal = 2;
						ACTIONActualisation();

					}
					//B
					if (x > (widthWin*0.75)  && x < (widthWin*0.84) && y > (heightWin-(heightWin*0.21)) && y < (heightWin-(heightWin*0.16)) ) {
						canal = 3;
						ACTIONActualisation();

					}
					// bt sauvegarder l'historique
					if (x > (widthWin*0.68)  && x < (widthWin*0.92) && y > (heightWin-(heightWin*0.14)) && y < (heightWin-(heightWin*0.09)) ) {
						//Récupere l'adresse de l'image
						printf("\nEntrez l'adresse de l'image (images/votre_image.ppm) : ");
						scanf("%s", adressH);			
						//Sauvegarde de l'histogramme
						SaveHisto(histo, adressH);
					}
				}
			}
		}

	}


	//Fonction pour la gestion du clavier
	fixeFonctionClavier(kbdFunc);
	fixeFonctionClavierSpecial(kbdSpFunc);
	fixeFonctionClicSouris(clickMouse);

	//Affichage des dessins (histogramme, boutons)
	fixeFonctionDessin(drawMain);

	//Application des lut s'il y en a qui sont passée en argument
	fristLut();
	//Fusion des calques
	pf = fusionCalque(pc);
	//Creation de l'histogramme
	histo = createHistogramme(pf, 0);
	//Création d'un element de l'historique redo fantome (avec aucune action)
	addHistory(p_redo, p_courant, -2);
	//Afficher les infos
	info(p_courant);
	//Creation de la fenetre
	initGLIMAGIMP_IHM(pf->widthImg,pf->heightImg,pf->tabPixel,pf->widthImg + 300,pf->heightImg+60);


	return 0;
}




