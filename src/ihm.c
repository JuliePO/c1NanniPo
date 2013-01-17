#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "outils.h"
#include "interface.h"
#include "image.h"
#include "calque.h"
#include "historique.h"
#include "histogramme.h"




void mondessin() {	

	/*header main-menu*/
	// variable: h1 : hauteur du bas, h2 : hauteur du haut, ht : hauteur du text
	float h1,h2,ht;
	h1 = 0.92;
	h2 = 0.97;
	ht = 0.94;

	fixeCouleur(0,0,0.6);

	drawCarre(0,0.895,1,1); //background bleu
	//style button quitter
	fixeCouleur(0.78,0.10,0.234);
	drawCarre(0.02,h1,0.05,h2);
	fixeCouleur(163,163,163);
	drawCarreVide(0.02,h1,0.05,h2);// gauche, bas, droite, haut
	writeString(0.03,ht,"X");

	//style btn sauvegarder
	fixeCouleur(0.30,0.30,0.30);
	drawCarre(0.07,h1,0.16,h2);
	fixeCouleur(163,163,163);
	drawCarreVide(0.07,h1,0.16,h2);// gauche, bas, droite, haut
	writeString(0.08,ht,"Sauver");

	// navigation dans l'historique
	//style btn undo/redo
	fixeCouleur(0.20,0.20,0.20);
	drawCarre(0.195,h1,0.28,h2); // bg undo
	drawCarre(0.28,h1,0.40,h2); // bg historique
	drawCarre(0.40,h1,0.48,h2); // bg redo
	fixeCouleur(1,1,1);
	drawCarreVide(0.195,h1,0.28,h2);// gauche, bas, droite, haut
	writeString(0.20,ht,"<- Undo");
	drawCarreVide(0.28,h1,0.40,h2);// gauche, bas, droite, haut
	writeString(0.29,ht,"Historique");
	drawCarreVide(0.40,h1,0.48,h2);// gauche, bas, droite, haut
	writeString(0.41,ht,"Redo ->");

	// navigation entre les sous menus
	fixeCouleur(0.20,0.20,0.20);
	drawCarre(0.65,h1,0.75,h2); // bg effets
	drawCarre(0.75,h1,0.85,h2); // bg Calques
	drawCarre(0.85,h1,0.975,h2); // bg histogramme
	fixeCouleur(1,1,1);
	drawCarreVide(0.65,h1,0.75,h2);// gauche, bas, droite, haut
	writeString(0.66,ht,"Effets");
	drawCarreVide(0.75,h1,0.85,h2);// gauche, bas, droite, haut
	writeString(0.76,ht,"Calques");
	drawCarreVide(0.85,h1,0.975,h2);// gauche, bas, droite, haut
	writeString(0.86,ht,"Histogramme");

	// bg sous-menu
	fixeCouleur(0.2,0.2,0.2);
	drawCarre(0.62,0,1,0.895);


}
void dessinMenuCalque() {
	
	mondessin();

	float h1,h2,ht;
	h1 = 0.92;
	h2 = 0.97;
	ht = 0.94;
	// position
	fixeCouleur(0.10,0.50,0.10);
	drawCarre(0.75,h1,0.85,h2); // bg Calques
	fixeCouleur(1,1,1);
	drawCarreVide(0.75,h1,0.85,h2);// gauche, bas, droite, haut
	writeString(0.76,ht,"Calques");

	//menu calque
	fixeCouleur(0.4,0.4,0.4);
	drawCarre(0.64,0.40,0.98,0.88);// gauche, bas, droite, haut
	fixeCouleur(0.1,0.1,0.1);
	writeString(0.65,0.82,"Calque :");

	drawCarreVide(0.74,0.80,0.84,0.85);// gauche, bas, droite, haut
	drawCarreVide(0.86,0.80,0.96,0.85);// gauche, bas, droite, haut
	drawCarreVide(0.74,0.74,0.96,0.79);// gauche, bas, droite, haut
	drawCarreVide(0.74,0.69,0.96,0.74);// gauche, bas, droite, haut
	drawCarreVide(0.74,0.64,0.96,0.69);// gauche, bas, droite, haut

	writeString(0.75,0.82,"<- prec");
	writeString(0.87,0.82,"suiv. ->");
	writeString(0.75,0.76,"+ avec image");
	writeString(0.75,0.71,"+ sans image");
	writeString(0.75,0.66,"- courant");

	drawCarreVide(0.74,0.55,0.78,0.60);// gauche, bas, droite, haut
	drawCarreVide(0.92,0.55,0.96,0.60);// gauche, bas, droite, haut
	writeString(0.756,0.57,"-  == Opacite ==  +");

	drawCarreVide(0.74,0.49,0.96,0.54);// gauche, bas, droite, haut
	writeString(0.75,0.51,"Rempli couleur ");

	drawCarreVide(0.74,0.43,0.78,0.48);// gauche, bas, droite, haut
	drawCarreVide(0.92,0.43,0.96,0.48);// gauche, bas, droite, haut
	writeString(0.756,0.45,"+  = Operation =  *");
}



void clickMouse(int button,int state,int x,int y) {
	//float widthWin = widthImg + 300;
	//float x1, x2, y1, y2;
	// button ajout de calque
	if (button == GLUT_LEFT_BUTTON) {
		if(state == GLUT_DOWN) {

			//x1 = widthWin - (widthWin - 0.63*widthWin);
			//cible du bouton ajout de calque (si image = image.ppm)
			if (x > 609 && x < 691 && y > 18 && y < 45) {
				fixeFonctionDessin(dessinMenuCalque);
					printf("%d %d\n",x,y);

			}
			


		}
	
	}
}





void info(Calque* p_courant) {
	printf("\n\n/************** IMAGIMP *************/\n\n");
	printf("Lorsque vous entrer des valeurs dans le terminal, il faut ensuite revenir sur l'image avant de taper d'autre commande.\n\n");
	printf("ID calque courant : %d\n", p_courant->id);
	printf("\n[F1] : Afficher l'aide\n\n");
}

void help(void) {
	printf("\n\n/-------------- MENU PRINCIPAL --------------/\n\n");
	printf("[p] : Afficher l'ID du calque courant\n");
	printf("[FLECHE HAUT] : Aller sur le calque suivant\n");
	printf("[FLECHE BAS] : Aller sur le calque précédent\n");
	printf("[q] : Aller sur un calque précis en donnant ID\n");
	printf("[c] : Afficher l'image courante ou l'image finale\n");
	printf("[l] : Afficher la liste de calque\n");
	printf("[ESQ] : Quitter IMAGIMP\n");

	printf("\n\n/-------------- MENU CALQUE --------------/\n\n");
	printf("[n] : Ajouter un calque vide\n");
	printf("[i] : Ajouter un calque avec une image\n");
	printf("[a] : Supprimer le calque courant\n");
	printf("[s] : Sauvegarder l'image finale\n");
	
	printf("\n\n[o] : Modifier l'opacite du calque courant.\n");
	printf("[m] : Modifier le mode d'opération du calque courant.\n");
	printf("[FLECHE GAUCHE] : Diminuer l'opacité du calque de 0 à 1\n");
	printf("[FLECHE DROITE] : Augmenter l'opacité du calque de 0 à 1\n");
	printf("[r] : Remplir le calque d'une couleur unie\n");

	printf("\n\n/-------------- MENU HISTORIQUE --------------/\n\n");
	printf("[x] : Afficher l'historique\n");
	printf("[z] : Annuler la derniere action\n");

	printf("\n\n/-------------- MENU HISTOGRAMME --------------/\n\n");
	printf("[t] : Afficher l'histogramme\n");
	printf("[w] : Changer le canal d'écoute de l'histogramme\n");
	printf("[h] : Sauvegarder l'histogramme en image ppm\n");
}

void removeAll(Image* p, Image* pf, Image* pic, LCalque* pc, LHistorique* ph, Histogramme* histo) {
	//Supprimer les images
	freeTabImg(p);
	freeTabImg(pf);
	freeTabImg(pic);

	//Supprimmer les listes de calque, l'historique et l'histogramme
	removeLCalque(pc); //Supprimer la liste de calque
	removeHistory (ph); //Supprimer l'historique
	removeHistogramme (histo); //Supprimer l'histogramme
}




