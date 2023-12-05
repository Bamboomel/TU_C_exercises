#include <stdio.h>
#include <stdlib.h>
#include "input2.h"

int main() {
    int n = lese_int();
    int laenge = n-1;
    int *array = (int*) malloc(laenge*sizeof(int));

    //alle Elemente in dem Array werden auf 1 gesetzt
    for (int i = 0; i < laenge ; i++) {
        array[i] = 1;
        //printf("%d", array[i]);
    }

    for (int i = 0; i < laenge ; i++) {
        //printf("%d", z);
        if (array[i] == 1){
            for (int x = 1; x < laenge ; x++) {
                array[i+x*(i+2)] = 0;
            }
            //printf("%d", array[i]);
        }
    }







    print_prim(array , laenge);
    free(array);
    return 0;
    }