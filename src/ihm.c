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

	fixeCouleur(1,1,1);
	writeString(0.84,0.90,"~~  MENU  ~~");// a 83% de la gauche, et a 85% du bas
	writeString(0.826,0.87,"~~  IMAGIMP  ~~");
	
	fixeCouleur(0.36,0.36,0.36);
	drawCarreVide(0.83,0.73,0.97,0.80);// gauche, bas, droite, haut
	writeString(0.84,0.76,"Ajout Calque");
	
	fixeCouleur(0.43,0.43,0.43);
	drawCarreVide(0.83,0.63,0.97,0.70);// gauche, bas, droite, haut
	writeString(0.84,0.66,"Suppr Calque");
	
	fixeCouleur(0.5,0.5,0.5);
	drawCarreVide(0.83,0.53,0.97,0.60);// gauche, bas, droite, haut
	writeString(0.845,0.56,"Enregistrer");
	
	fixeCouleur(0.57,0.57,0.57);
	drawCarreVide(0.83,0.43,0.97,0.50);// gauche, bas, droite, haut
	writeString(0.8675,0.46,"Finale");
	
	fixeCouleur(0.64,0.64,0.64);
	drawCarreVide(0.83,0.35,0.97,0.40);// gauche, bas, droite, haut
	writeString(0.87,0.3675,"Calque");
	
	fixeCouleur(0.64,0.64,0.64);
	drawCarreVide(0.83,0.25,0.89,0.32);// gauche, bas, droite, haut
	writeString(0.84,0.28,"Prec");
	
	fixeCouleur(0.64,0.64,0.64);
	drawCarreVide(0.91,0.25,0.97,0.32);// gauche, bas, droite, haut
	writeString(0.92,0.28,"Suiv");
	
	fixeCouleur(0.72,0.72,0.72);
	drawCarreVide(0.83,0.15,0.89,0.23);// gauche, bas, droite, haut
	writeString(0.84,0.1825,"Undo");
	
	fixeCouleur(0.72,0.72,0.72);
	drawCarreVide(0.91,0.15,0.97,0.23);// gauche, bas, droite, haut
	writeString(0.92,0.1825,"Redo");
	
	fixeCouleur(0.78,0.10,0.234);
	drawCarreVide(0.83,0.04,0.97,0.11);// gauche, bas, droite, haut
	writeString(0.865,0.065,"Quitter");
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
	printf("[c] : Afficher l'image courante ou l'image final\n");
	printf("[l] : Afficher la liste de calque\n");
	printf("[ESQ] : Quitter IMAGIMP\n");

	printf("\n\n/-------------- MENU CALQUE --------------/\n\n");
	printf("[n] : Ajouter un calque vide\n");
	printf("[i] : Ajouter un calque avec une image\n");
	printf("[a] : Supprimer le calque courant\n");
	printf("[s] : Sauvegarder l'image final\n");
	
	printf("\n\n[o] : Modifier l'opacite du calque courant.\n");
	printf("[m] : Modifier le mode d'opération du calque courant.\n");
	printf("[FLECHE GAUCHE] : Diminuer l'opacite du calque de à 0.1\n");
	printf("[FLECHE DROITE] : Augmenter l'opacite du calque de à 0.1\n");
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


