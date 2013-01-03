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
	Image image;
	Image* p = &image;
	char name[]="../images/image.ppm";
	openImg(p, name);
	printf("%c%c\n %d %d\n %d\n", p->magicNumber[0], p->magicNumber[1], p->heightImg, p->widthImg, p->maxValue);
	initGLIMAGIMP_IHM(p->widthImg,p->heightImg,p->tabPixel,p->widthImg,p->heightImg);
	return 0;
}
