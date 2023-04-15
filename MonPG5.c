#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char *argv[])
{
	int total = 0;
	int compteur = 0;
	int isFinish = 0;
	int length,i; 
	char input[100] = "";

	// Tant qu'on entre des nombres, le programme continue
	while(isFinish != 1) {
		printf("Ajoutez une valeure à la moyenne (saisissez n'importe quel caractère pour calculer) : ");
		scanf ("%s", input);
		length = strlen (input);
		int isNumber = 1;
		// On vérifie qu'il n'y a que des chiffres (si non => le boolean passe à faux)
		for (i = 0; i < length; i++) {
			if (!isdigit(input[i])) isNumber = 0;
		}
		// S'il n'y a que des chiffres on incrémente les variables permettant de calculer la moyenne
		if(isNumber == 1) {
			compteur++;
			total += atoi(input);
		// Si ce n'est pas un chiffre => on ferme le programme et affiche la moyenne
		} else {
			isFinish = 1;
			printf("Voici la moyenne des valeurs données : %d\n", total/compteur);
		}
	}
	return EXIT_SUCCESS;
}
	