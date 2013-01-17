#ifndef IHM_H
#define IHM_H
#include <stdio.h>
#include <stdlib.h>
#include "outils.h"
#include "interface.h"
#include "image.h"
#include "calque.h"
#include "historique.h"
#include "histogramme.h"

/************* Appel des fonctions *************/
void drawMain();
void drawMenuLayer();
void drawMenuHistogramme();
void drawMenuLut();
void info(Calque*);
void help();
void removeAll(Image*, Image*, Image*, LCalque*, LHistorique*, Histogramme*);


#endif
