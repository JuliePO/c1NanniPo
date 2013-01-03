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

int main(void) {
	
	LCalque calque;
	LCalque* pc = &calque;
	pc = new_LCalque();

	Image image;
	Image* p = &image;
	char name[]="../images/daisuke.ppm";
	openImg(p, name);
	returnImage(p);

	pc = addCalqueImg(pc, 0, 0, p);

	initGLIMAGIMP_IHM(p->widthImg,p->heightImg,p->tabPixel,p->widthImg + 30,p->heightImg);


	return 0;
}
