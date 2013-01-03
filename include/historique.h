#ifndef HISTORIQUE_H
#define HISTORIQUE_H
#include <stdio.h>
#include <stdlib.h>

/************* Structure de l'historique *************/
typedef struct Historique
{
    int donnee; /* La donnée que notre pile stockera. */
    struct Historique *prev; /* Pointeur vers l'élément précédent de la pile. */
} Historique;

/************* Appel des fonctions *************/

#endif
