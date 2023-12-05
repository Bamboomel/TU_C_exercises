#include <stdio.h>
#include <stdlib.h>

void print_array(int array[], int len) {
    printf("Array: ");

    for (int i = 0; i < len ; i++) {
        printf("%d", array[i]);

        if (i < len-1){
            printf(", ");
        }
        else {
            printf("\n");
        }
    }
}


void sum(int array[], int len, int *p){
    int summe = 0;

    for (int i = 0; i < len; i++) {
        summe = summe + array[i];

        if (i == len-1){
            *p = summe;
        }
    }
}


int min(int array[], int len){
    int minimum = array[0];

    for (int i = 0; i < len; i++) {

        if (minimum > array[i]) {
            minimum = array[i];
        }

        if (i == len - 1) {
            return minimum;
        }
    }
    return 0;
}


int max(int array[], int len){
    int maximum = 0;

    for (int i = 0; i < len; i++) {

        if (maximum < array[i]) {
            maximum = array[i];
        }

        if (i == len - 1) {
            return maximum;
        }
    }
    return 0;
}



int main() {
    int array[] = {9, 4, 7, 8, 10, 5, 1, 6, 3, 2};
    int len = 10;
    print_array(array, len);
    printf("Minimum: %d\n", min(array, len));
    printf("Maximum: %d\n", max(array, len));
    int s;
    sum(array, len, &s);
    printf("Summe: %d\n", s);
    }