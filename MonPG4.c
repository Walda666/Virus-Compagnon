#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int prix,reponse;
    srand(time(NULL));
    prix = rand()%100;

    printf("Devinez le prix\n");

    for (int i = 0; i < 10; i++) {
        printf("Entrez votre nombre : ");
        scanf("%d",&reponse);

        if(reponse < prix ){
            printf("PLus grand\n\n");
        } else if (reponse > prix) {
            printf("Plus petit\n\n");
        } else {
            printf("Bravo\n");
            break;
        }

    }

    if(reponse != prix) {
        printf("Vous avez épuisé toutes vos chances. Le prix était %d\n",prix);
    }
    return 0;
}