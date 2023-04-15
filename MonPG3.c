#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 100

int main() {
    char phrase[MAX_LENGTH];
    char plus_long_mot[MAX_LENGTH];
    int x, y, taille_actuelle, plus_grand;

    printf("Entrez une phrase : ");
    scanf("%[^\n]", phrase);

    plus_grand = 0;

    // Parcourt chaque mot
    for (x = 0; x < strlen(phrase); x++) {
        if (phrase[x] == ' ' || phrase[x] == ',' || phrase[x] == '.' || phrase[x] == ';') {
            continue;
        }

        taille_actuelle = 0;

        // Parcourt chaque caractère du mot
        for (y = x; y < strlen(phrase); y++) {
            if (phrase[y] == ' ' || phrase[y] == ',' || phrase[y] == '.'|| phrase[y] == ';') {
                break;
            }

            // Incrémente la longueur courante du mot
            taille_actuelle++;
        }

        if (taille_actuelle > plus_grand) {
            plus_grand = taille_actuelle;
            strncpy(plus_long_mot, phrase + x, plus_grand);
        }
    }

    // Ajoute le caractère de fin de chaîne à la fin du mot le plus long
    plus_long_mot[plus_grand] = '\0';

    // Affiche le mot
    printf("Le mot le plus long est : %s\n", plus_long_mot);

    return 0;
}