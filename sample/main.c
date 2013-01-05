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

/// ///////////////////////////////////////////////////////////////////////////
/// fonction de personnalisation du rendu
void mondessin() {
	writeString(0,0,"Ecriture ecran");
	fixeCouleur(1.0,0.0,0.0);
	drawLigne(0.0,0.0,1.0,1.0);
	fixeCouleur(1.0,1.0,0.0);
	drawCarre(0.5,0.5,0.7,0.7);
	fixeCouleur(1.0,0.0,0.0);
	drawCarreVide(0.85,0.2,0.95,0.25);
	writeString(0.86/**800+1*/,0.21/**600+1*/,"TEST");
	drawDisque(0.1,0.5,0.1);
	drawDisque(0.3,0.5,0.1);
	drawDisque(0.5,0.5,0.1);
	drawDisque(0.7,0.5,0.1);
	drawDisque(0.9,0.5,0.1);
	fixeCouleur(0.0,0.0,1.0);
	drawCercle(0.7,0.5,0.02);
	fixeCouleur(1.0,1.0,1.0);
}


int main(void) {
	
	LCalque calque;
	LCalque* pc = &calque;
	pc = new_LCalque();

	Image image;
	Image* p = &image;
	char name[]="../images/daisuke.ppm";
	openImg(p, name);

	Image image2;
	Image* p2 = &image2;
	char name2[]="../images/image.ppm";
	openImg(p2, name2);

	Image image_final;
	Image* pf = &image_final;

	pc = addCalqueImg(pc, 0.5, 0, p);
	//pc = addCalque(pc, 1, 0);
	//pc = addCalqueImg(pc, 0.5, 0, p2);

	printf("%d\n", pc->length);

	pf = fusionCalque(pc);

	initGLIMAGIMP_IHM(pf->widthImg,pf->heightImg,pf->tabPixel,pf->widthImg + 30,pf->heightImg);


	return 0;
}
