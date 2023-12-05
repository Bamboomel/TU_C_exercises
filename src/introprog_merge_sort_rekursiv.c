#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "introprog_input_merge_sort.h"

/*
 * Diese Funktion fügt zwei bereits sortierte Arrays zu einem
 * sortierten Array zusammen
 *
 *
 * array : Pointer auf das Array
 * first : Index des ersten Elements (Beginn) des (Teil-)Array
 * middle: Index des mittleren Elements des (Teil-)Array
 * last  : Index des letzten Elements(Ende) des (Teil-)Array
 */


void merge(int* array, int first, int middle, int last){
    // HIER Funktion merge() implementieren

    int *array_b = (int *) malloc((last - first + 1) * sizeof(int));
    int links = first;
    int rechts = middle + 1;
    int countMerge = 0;
    int j = 0;


    while((links <= middle) && (rechts <= last)){
        if(array[links] <= array[rechts]){
            array_b[countMerge] = array[links];
            links++;
        }else{
            array_b[countMerge] = array[rechts];
            rechts++;
        }
        countMerge++;
    }

    while(links <= middle){
        array_b[countMerge] = array[links];
        links++;
        countMerge++;
    }

    while(rechts <= last){
        array_b[countMerge] = array[rechts];
        rechts++;
        countMerge++;
    }

//    printf("----start orig list ----\n");
//    for (int i = first; i < last + 1; i++) {
//        printf("%d ", array[i]);
//    }
//    printf("\n");
//    printf("----end orig list ----\n");
//
//    printf("----start sorted list ----\n");
//    for (int i = 0; i < countMerge; i++) {
//        printf("%d ", array_b[i]);
//    }
//    printf("\n");
//    printf("----end sorted list ----\n");

    while(j < countMerge){
        array[first + j] = array_b[j];
        j++;
    }
    //printf("%d, %d, %d\n", first, countMerge, j);


    free(array_b);

}

/*
 * Diese Funktion implementiert den rekursiven Mergesort
 * Algorithmus auf einem Array. Sie soll analog zum Pseudocode
 * implementiert werden.
 *
 * array: Pointer auf das Array
 * first: Index des ersten Elements des (Teil-)Array
 * last:  Index des letzten Elements des (Teil-)Array
 */
void merge_sort(int* array, int first, int last){
  // HIER Funktion merge_sort() implementieren

  if(first < last){
      int middle = ((first + last) / 2);
      merge_sort(array, first, middle);
      merge_sort(array, middle + 1, last);
      merge(array, first, middle, last);
  }

}

/*
 * Hauptprogramm.
 *
 * Liest Integerwerte aus einer Datei und gibt diese sortiert im
 * selben Format über die Standardausgabe wieder aus.
 *
 * Aufruf: ./introprog_merge_sort_rekursiv <maximale anzahl> \
 *         <dateipfad>
 */
int main (int argc, char *argv[])
{
    if (argc!=3){
        printf ("usage: %s <maximale anzahl>  <dateipfad>\n", argv[0]);
        exit(2);
    }
    
    char *filename = argv[2];
    
    // Hier array initialisieren
    int *array = (int *) malloc(atoi(argv[1]) * sizeof(int));

    
    int len = read_array_from_file(array, atoi(argv[1]), filename);

    printf("Eingabe:\n");
    print_array(array, len);

    // HIER Aufruf von "merge_sort()"
    merge_sort(array, 0, len - 1);

    printf("Sortiert:\n");
    print_array(array, len);

    free(array);

    return 0;
}
