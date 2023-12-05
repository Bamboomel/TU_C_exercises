#include <stdio.h>
#include <stdlib.h>
#include "input.h" // Hier binden wir die Bibliothek ein

int fibonacci(int n) {
    if(n <= 2) {
        return 1;
    }
    else {
        int f = fibonacci(n-1) + fibonacci(n-2);
        return f;
    }
}

//1 1 2 3 5 8 13

int main(){
    int n = lese_int (); // Hier rufen wir die Funktion lese_int auf.
    int f = fibonacci(n);
    printf("Fib(%d) = %d\n" , n, f);

    return 0; //Beende das Programm ohne Fehlermeldung
    }