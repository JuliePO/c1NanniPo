//ficher servant à déclarer les fonctions qui feront des opérations sur les images
//il faut aussi creer un .h 
//Structure IMAGE

typedef struct structure_image 
	{
	// Numéro de variante
	char numVar;
	
	// Hauteur et largeur de l'image
	unsigned int hauteurImg;
	unsigned int largeurImg;
	
	// Valeur maximale
	int valMax;
	
	// Valeur des pixels
	unsigned char* tabPixel; 
	}str_Img;
