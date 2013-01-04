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
