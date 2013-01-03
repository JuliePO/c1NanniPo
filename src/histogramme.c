Histogramme* createHistogramme(Image* img, int mode) {
	Histogramme* histo;
	int moyenne = 0, startIndex = 0, int value = 0, i;

	histo= (Histogramme*)malloc(sizeof(Histogramme));
	histo->mode = mode;

	for(i=0; i<256; i++) {
		histo->values[i] = 0;
	}
	
	if(mode>=0 || mode<=3) {
		// mode = 0 : Création de l'histogramme à partir des moyennes des valeurs RVB
		if(mode == 0) {
			for(i = 0; i < (img->heightImg) * (img->widthImg) * 3; i += 3) {
			//Moyenne des couleurs RVB
			moyenne = (((int)img->tabPixels[i] + (int)img->tabPixels[i+1] + (int)img->tabPixels[i+2]) / 3);
			histo->values[moyenne]++;
			}
		}
		// mode != 0 : Création de l'histogramme en fonction d'un canal
		else {
			switch(mode) {
				//Rouge
				case 1 :
					break;
				//Vert
				case 1 :
					startIndex = 1;
					break;
				//Bleu
				case 1 :
					startIndex = 2;
					break;
			}
		
			for(i = startIndex; i < (img->heightImg) * (img->widthImg) * 3; i += 3){
				value= (int)img->tabPixels[i];
				histo->values[value]++;
		}
		return histo;
	}
	else {
		printf("Erreur : mode incompatible");
		return NULL;
	}
}
