#include <stdlib.h>
#include <stdio.h>
 
int main(int argc, char *argv[])
{
	// Simple scanner + conversion avec une multiplication
	double taille = 0;
	printf("Entrez votre taille en mètres : ");
	scanf("%lf", &taille);
	double taillePieds = taille*3.2808;
	printf("Votre taille en pieds est %lf !\n", taillePieds);
    return EXIT_SUCCESS;
}
