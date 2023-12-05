#include <stdio.h>
#include <stdlib.h>

int main() {
    int breite = 6;
    int hoehe = 3;

    //äußere Schleife zum Durchlaufen der Zeichen
    for (int i = 0; i < (hoehe + 2); i++) {

        //Bedingung für oberste und unterste Zeile
        if (i == 0 | i == (hoehe + 1)) {
            //innere Schleife zum Durchlaufen der Spalten
            for (int j = 0; j < (breite +2); j++) {
                printf("A");
            }
        }
        else {
            //innere Schleife zum Durchlaufen der Spalten
            printf("A");
            for (int j = 0; j < breite ;j++) {
                printf("B");
            }
            printf("A");
        }
        printf("\n");
    }

}
