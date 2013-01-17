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

//LUT liste
LLUT liste_lut;
LLUT* p_llut = &liste_lut;

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
	int intensite;

	/****** INITIALISATION DES ELEMENTS *****/

	//Initialisation de l'historique
	ph = initHistory();
	
	//Initialisation de la liste des calques
	pc = new_LCalque();

	//Initialisation de la liste des lut
	p_llut=new_LLUT();

	//Calque courant
	p_courant = pc->p_head;

	//Chargement de la première image
	if(addCalqueImg(pc, 1, 0, argv[1]) == 1) {
		//Calque courant
		p_courant = pc->p_head;
		//Ajout à l'historique
		addHistory(ph, p_courant, 0);
	}
	else {
		printf("Erreur : Probleme à l'ajout du premier calque\n");
		exit(1);
	}

	/********* Affichage de l'histogramme *********/
	void afficheHisto() {
		//appel du menu principal
		mondessin();
		//appel du sous menu histogramme
		dessinMenuHistogramme();

		int i=0, j;
		float value;

		//Fond blanc de l'histogramme
		fixeCouleur(0.7,0.8,0.7);
		drawCarre(0.64,0.38,0.98,0.87);

		//Battonnet noir pour afficher l'histogramme
		fixeCouleur(0,0,0);
		//Dessin un baton qui a la hauteur de la valeur en pourcentage 
		for(j=256; j>=0; j--) {

			value = (0.473*((histo->values[j])/100.0))+0.40; //Met les valeurs en pourcentage
			drawLigne((((0.34*i)/255)+0.64),0.38,(((0.34*i)/255)+0.64),value);
			i++;
		}
	}

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
		addCalqueImg(pc, opacity, mix, adress);
		//Le calque courant devient le calque qu'on vient d'ajouter
		p_courant = pc->p_tail;
		//Ajout de l'action dans l'historique
		addHistory(ph, p_courant, 0);
		addHistory(p_redo, p_courant, -1);
	}

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

	/****** GESTION TOUCHES CLAVIER ******/
	void kbdFunc(unsigned char c, int x, int y) {
	
		switch(c) {
			//Touche p : Afficher l'id du calque courant
			case 'p' :
				printf("\nID du calque courant : %d\n", p_courant->id);
				break;

			//Touche q : Naviger dans la liste de calque
			case 'q' : 
				printf("\nEntrer l'id du calque :");
				scanf("%d", &position);

				//Le calque courant devient le calque qui a l'id entré par l'utilisateur
				p_courant = navCalque (pc, p_courant, position);
				//Afficher l'id du calque courant
				printf("ID du calque courant : %d \n", p_courant->id);
				break;

			//Touche c : Changer le mode de vue : 0 = Image final et 1 = calque courant
			case 'c' :
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

			//Touche l : Afficher la liste de calque
			case 'l' :
				afficheLCalque(pc);
				break;

			//Touche n : Ajouter un nouveau calque vide
			case 'n' :

				ACTIONaddCalqueVide();
				break;

			//Touche i : Ajouter un calque avec une image
			case 'i' :	
				ACTIONaddCalqueImg();
			
				break;

			//Touche a : Supprimer le calque courant
			case 'a' :
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
					printf("Le calque a bien été supprimer\n");
				}
				else
					printf("Il reste un seul calque, impossible de le supprimer");
				break;

			//Touche s : Sauvegarde de l'image final
			case 's' :
				//Recuperer l'adresse de l'image final
				printf("\nEntrez l'adresse de l'image (images/votre_image.ppm) : ");
				scanf("%s", adressF);

				//Si la sauvegarde a été faite alors affiche l'adresse
				if(saveImg(pf, adressF) == 1)
					printf("L'image a bien ete enregistree dans %s\n", adressF);
				else
					printf("Ereur dans la sauvegarde de l'image\n");
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

			//Touche r : Remplir le calque d'une couleur unie
			case 'r' :

				//Récupère la valeur de rouge
				printf("\nEntrer la valeur rouge (comprise entre 0 et 255) :");
				scanf("%d", &red);

				//Si la valeur n'est pas comprise entre 0 et 255 alors on redemande jusqu'à que c'est bon
				if(red < 0 || red > 255) {
					while(red < 0 || red > 255) {
						printf("Erreur entrez une valeur comprise entre 0 et 255 \n");
						printf("Entrer la valeur rouge :");
						scanf("%d", &red);
					}
				}

				//Récupère la valeur de vert
				printf("Entrer la valeur vert (comprise entre 0 et 255) :");
				scanf("%d", &green);

				//Si la valeur n'est pas comprise entre 0 et 255 alors on redemande jusqu'à que c'est bon
				if(green < 0 || green > 255) {
					while(green < 0 || green > 255) {
						printf("Erreur entrez une valeur comprise entre 0 et 255 \n");
						printf("Entrer la valeur rouge :");
						scanf("%d", &green);
					}
				}

				//Récupère la valeur de bleu
				printf("Entrer la valeur blue (comprise entre 0 et 255) :");
				scanf("%d", &blue);

				//Si la valeur n'est pas comprise entre 0 et 255 alors on redemande jusqu'à que c'est bon
				if(blue < 0 || blue > 255) {
					while(blue < 0 || blue > 255) {
						printf("Erreur entrez une valeur comprise entre 0 et 255 \n");
						printf("Entrer la valeur rouge :");
						scanf("%d", &blue);
					}
				}

				//Rempli le calque par la couleur
				remplirCalque(p_courant, red, green, blue);
				//Ajout de l'action dans l'historique
				addHistory(ph, p_courant, 4);
				break;

			//Touche x : Afficher l'historique
			case 'x' :
				AfficheHistory(ph);
				break;
			//Touche z : Annuler la derniere action
			case 'z' :
				//Annule la derniere action
				cancelHistory(ph, pc, p_redo);
				break;
			//Touche d : Redo
			case 'd' : 
				redoHistory (p_redo, pc, ph);
				break;

			//Touche f : Affiche Historique redo
			case 'f' :
				AfficheHistory(p_redo);
				printf("taille : %d\n\n", p_redo->length);
				break;
				
			//Touche t : Afficher l'histogramme
			case 't' : 
				fixeFonctionDessin(afficheHisto);
				break;


			//Touche w : Changement de canal d'écoute pour l'histogramme
			case 'w' :
				//Le canal avant changement
				printf("Canal : %d", canal);
				//Récupère le nouveau canal
				printf("Entrer le nouveau canal (0 : global, 1 : rouge, 2 : vert, 3 : bleu) : ");
				scanf("%d", &canal);

				//Si le canal n'est pas 0, 1, 2 ou 3 alors on redemande jusqu'à que c'est bon
				if(canal != 0 && canal != 1 && canal != 2 && canal != 3) {

					while(canal != 0 && canal != 1 && canal != 2 && canal != 3) {
						printf("Erreur entrez une valeur (0 : global, 1 : rouge, 2 : vert, 3 : bleu)\n");
						printf("Entrer le canal :");
						scanf("%d", &canal);
					}
				}
				break;

			//Touche h : Sauvegarde de l'histogramme en image ppm
			case 'h' : 
				//Récupere l'adresse de l'image
				printf("\nEntrez l'adresse de l'image (images/votre_image.ppm) : ");
				scanf("%s", adressH);			
				//Sauvegarde de l'histogramme
				SaveHisto(histo, adressH);
				break;

			//Touche u rajouter une lut
			case 'u' : 
				

				invert(p_llut);
				printf("invert OK\n");
				
				break;

			case 'y' :
				if (p_llut != NULL) {
					//Création du calque temporaire pour parcourrir la liste de calque
					LUT *p_temp = p_llut->l_head;

					//Parcourt la liste de calque
					while (p_temp != NULL) {
						applyLUT(pic, p_temp);
					    	p_temp = p_temp->l_next;
					}
					free(p_temp);
				}
				break; 

			case 'g' : 
				//Afficher autre chose
				fixeFonctionDessin(mondessin);
				

				break;

			//Touche Escape : fin du programme
			case 27 :
				printf("Fin du programme\n");
				
				//Supprimer les elements 
				removeAll(p, pf, pic, pc, ph, histo);

				//Fin du programme
				exit(0);
				break;

			//Les autres touches
			default :
				printf("Touche non attribuer\n");
		}
		
		//Si switchCalque = 0 (mode image final)
		if(switchCalque == 0) {
			fusionCalque(pc, pf); //Fusion des calques
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
				}
				//Ajout de l'action dans l'historique
				addHistory(ph, p_courant, 2);
				break;

			//Touche FLECHE DE DROITE : Augmente l'opacite du calque
			case GLUT_KEY_RIGHT :
				//Si l'opacite est à 1 (maximum)
				if(p_courant->opacity >= 1)
					printf("Opacite est dejà à 100\n");
				else {
					p_courant->opacity += 0.1; //Augmente de 0.1 l'opacite de calque
					printf("Opacite : %f\n", p_courant->opacity); 
				}
				//Ajout de l'action dans l'historique
				addHistory(ph, p_courant, 2);
				break;

			//Les autres touches
			default :
				printf("Touche non attribuer\n");
		}

		//Si switchCalque = 0 (mode image final)
		if(switchCalque == 0) {
			fusionCalque(pc, pf); //Fusion des calques
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

	/* GESTION CLICKS SOURIS = BOUTONS*/
	void clickMouse(int button,int state,int x,int y) {
		int widthWin = pf->widthImg + 300; //= 512
		int heightWin = pf->heightImg + 60;
		// button ajout de calque
		if (button == GLUT_LEFT_BUTTON) {
			if(state == GLUT_DOWN) {


				/*****header : Menu principal ****/

				//bouton quitter 
				if (x > (widthWin*0.02)  && x < (widthWin*0.05) && y > (heightWin-(heightWin*0.97)) && y < (heightWin-(heightWin*0.92)) ) {
					printf("Fin du programme\n");
					//Supprimer les elements 
					removeAll(p, pf, pic, pc, ph, histo);
					//Fin du programme
					exit(0);
				}
				if (x > (widthWin*0.07)  && x < (widthWin*0.16) && y > (heightWin-(heightWin*0.97)) && y < (heightWin-(heightWin*0.92)) ) {
					fixeFonctionDessin(dessinMenuLut);

				}
				//bt menu lut
				if (x > (widthWin*0.65)  && x < (widthWin*0.75) && y > (heightWin-(heightWin*0.97)) && y < (heightWin-(heightWin*0.92)) ) {
					fixeFonctionDessin(dessinMenuLut);
					menu=1;

				}
				//bt menu calque (si image = image.ppm)
				if (x > (widthWin*0.75)  && x < (widthWin*0.85) && y > (heightWin-(heightWin*0.97)) && y < (heightWin-(heightWin*0.92)) ) {
					fixeFonctionDessin(dessinMenuCalque);
					menu=2;
					printf("%d\n", menu);

				}
				//bt menu histogramme
				if (x > (widthWin*0.86)  && x < (widthWin*0.975) && y > (heightWin-(heightWin*0.97)) && y < (heightWin-(heightWin*0.92)) ) {
					fixeFonctionDessin(afficheHisto);
					menu=3;
				}

					/******** Sous menu calque *************/


					if (menu == 2) {
						// navigation calque précédent
						// navigation calque suivant
						//bt Ajout de calque avec sans image
						if (x > (widthWin*0.74)  && x < (widthWin*0.96) && y > (heightWin-(heightWin*0.79)) && y < (heightWin-(heightWin*0.74)) ) {
							ACTIONaddCalqueVide();
						}
						//bt Ajout de calque avec une Image	
						if (x > (widthWin*0.74)  && x < (widthWin*0.96) && y > (heightWin-(heightWin*0.74)) && y < (heightWin-(heightWin*0.69)) ) {
							ACTIONaddCalqueImg();
						}
					}

					



			}
		
		}
	}


	//Fonction pour la gestion du clavier
	fixeFonctionClavier(kbdFunc);
	fixeFonctionClavierSpecial(kbdSpFunc);
	fixeFonctionClicSouris(clickMouse);


	//Fusion des calques
	fusionCalque(pc, pf);
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




