#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "introprog_input_merge_sort.h"

//definieren einer min funktion
int min(int a, int b) {
    int result;

    if (a < b) {
        result = a;
    }else {
        result = b;
    }

    return result;
}
/*
 * Diese Funktion fügt zwei bereits sortierte Arrays zu einem
 * sortierten Array zusammen
 *
 * array : Pointer auf das Array
 * first : Index des ersten Elemements (Beginn) des (Teil-)Array
 * middle: Index des mittleren Elements des (Teil-)Array
 * last  : Index des Letzten Elements (Ende) des (Teil-)Array
 */
void merge(int* array, int first, int middle, int last){
    // HIER Funktion merge() implementieren

    //Übernahme des Codes von der Aufgabe 07-01
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

    while(j < countMerge){
        array[first + j] = array_b[j];
        j++;
    }
    //printf("%d, %d, %d\n", first, countMerge, j);


    free(array_b);
}

/*
 * Diese Funktion implementiert den iterativen Mergesort
 * Algorithmus auf einem Array. Sie soll analog zum Pseudocode
 * implementiert werden.
 *
 * array:  Pointer auf das Array
 * last :  Index des letzten Elements
 */
void merge_sort(int* array, int last){
    // HIER Funktion merge_sort() implementieren
    //Initialisierung und zuweisung Hilfsvarible d. Schrittweite
    int step = 1;

    //implementierung Pseudocode aus Listing 3
    //Schleife zum durchlaufen des gesamten arrays
    while(step <= last){
        int left = 0;
        //Schleife zum sortieren des linken Teilarrays
        while(left <= last - step){
            int mid = left + step - 1;
            mid = min(mid, last);
            int right = left + 2 * step - 1;
            right = min(right,last);
            //Aufruf merge Funktion
            merge(array, left, mid, right);
            left = left + 2 * step;
        }
        step = step * 2;
    }

}

/*
 * Hauptprogramm.
 *
 * Liest Integerwerte aus einer Datei und gibt diese sortiert im
 * selben Format über die Standardausgabe wieder aus.
 *
 * Aufruf: ./introprog_merge_sort_iterativ <maximale anzahl> \
 * 	   <dateipfad>
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
    merge_sort(array, len - 1);

    printf("Sortiert:\n");
    print_array(array, len);

    free(array);

    return 0;
}
