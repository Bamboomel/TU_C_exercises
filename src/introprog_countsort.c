#include <stdio.h>
#include <stdlib.h>
#include "arrayio.h"

int MAX_LAENGE = 1000;
int MAX_VALUE = 100;

void count_sort_calculate_counts(int input_array[], int len, int count_array[]) {
    /* Hier Funktion implementieren*/



    //count_array mit nullen initiallisieren
    for (int j = 0; j < MAX_VALUE+1; j++) {
        count_array[j]=0;
    }

    //Anzahl der jeweiligen Werte im count_array ablegen
    for (int i = 0; i < len; i++) {
        count_array[input_array[i]]++;
    }

}

void count_sort_write_output_array(int output_array[], int len, int count_array[]) {
    /* Hier Funktion implementieren */
    //print_array(output_array,len);
    for (int z = 0; z < len; z++) {
        output_array[z] = 0;
    }
    //print_array(count_array,MAX_VALUE+1);

    int key = 0;
    for (int i = 0; i < MAX_VALUE+1; i++) {
        for (int j = 0; j < count_array[i]; j++) {
            //printf("j: %d\n i: %d\n", j, i );
            //printf("k: %d\n", key);
            output_array[key] = i;
            key++;
        }
    }
}



int main(int argc, char *argv[]) {

    if (argc < 2){
        printf("Aufruf: %s <Dateiname>\n", argv[0]);
        printf("Beispiel: %s zahlen.txt\n", argv[0]);
        exit(1);
    }

    char *filename = argv[1];

    int input_array[MAX_LAENGE];
    int len = read_array_from_file(input_array, MAX_LAENGE, filename);

    printf("Unsortiertes Array:");
    print_array(input_array, len);

    /*
     * Hier alle nötigen Deklarationen und Funktionsaufrufe für
     * Countsort einfügen!
     */
    //Deklarieren der arrays
    int count_array[MAX_VALUE+1];
    int output_array[len];

    //Ausführen der Funktionen
    count_sort_calculate_counts(input_array, len, count_array);
    count_sort_write_output_array(output_array, len, count_array);

    printf("Sortiertes Array:");

    /* Folgende Zeile einkommentieren, um das Array auszugeben! */
    print_array(output_array, len);

    return 0;
}
