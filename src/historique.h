#ifndef HISTORIQUE_H
#define HISTORIQUE_H
#include <stdio.h>
#include <stdlib.h>
#include "calque.h"

/************* Structure de l'historique *************/
typedef struct Historique
{

	int action; //type opération/action que l'on fait
	Calque* calqueH; //pointeur calque sur lequel l'action est appliqué

	// Pointeur vers l'élément précédent de la pile. 
	struct Historique *prev; 

} Historique;

typedef struct LHistorique {

	//Taille de la liste
	size_t length;

	//Pointeur
	Historique *head; //pointeur vers le premier element = début de la pile
}LHistorique;

/************* Appel des fonctions *************/
LHistorique* initHistory (void);
int addHistory (LHistorique*, Calque*, int);
void AfficheHistory (LHistorique*);
void cancelHistory (LHistorique*, LCalque*, LHistorique*);
void redoHistory (LHistorique*, LCalque*, LHistorique*);
void removeHistory (LHistorique*);
#endif
