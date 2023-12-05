#include <stdio.h>
#include <stdlib.h>

int main() {
    int nummer = 105; // Probiere verschiedene Werte aus: 101, 103, ...
    printf("Ist %d eine Primzahl?\n", nummer);

    for (int i = 2; i < (nummer/2); i++) {
        if ((nummer % i) == 0) {
            printf("Nein\n");
            return 0;
        }
    }
    printf("Ja\n");
    return 0;
}