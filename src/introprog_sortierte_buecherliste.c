#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "introprog_structs_lists_input.h"

int MAX_STR = 255;

/* Bewirkt, dass statt 'struct _element' auch 'element' verwendet
 * werden kann.
 */
typedef struct _element element; 

/* Bewirkt, dass statt 'struct _list' auch 'list' verwendet werden
 * kann.  Hier in einem geschrieben, so dass man auch 'list'
 * innerhalb der struct-Definition selbst verwenden kann.
 */
typedef struct _list { /* Separater Wurzelknoten */
    element *first;    /* Anfang/Kopf der Liste */
    int count;         /* Anzahl der Elemente */
} list;

/* HIER struct _element implementieren. */
typedef struct _element {
    char title[255];           //char array title mit der länge 255 reservieren
    char author[255];          //char array author mit der länge 255 reservieren
    int year;                  //int year initiieren
    long long int isbn;        //long long int isbn initiieren
    element* next;             //pointer next für das nächste Element
} element;

/* Fuege ein Element in die Liste ein, sodass die Liste aufsteigend
 * nach ISBN sortiert ist.  Dafür muss das erste Element ermittelt
 * werden, das in der bisher sortierten Liste eine ISBN besitzt,
 * die größer ist als die des neuen Elements.  Wenn die Liste leer
 * ist, soll das Element direkt an den Anfang platziert werden.
 *
 * first    - Pointer auf das erste Element (bzw. Anfang) der Liste
 * new_elem - Pointer auf das neues Element das in die Liste
 * eingefuegt werden soll
 *
 * Gib einen Pointer auf den neuen oder alten Anfang der Liste
 * zurueck.
 */
element* insert_sorted(element *first, element *new_elem) {
    /* HIER implementieren. */
    element* book = first;                                  //Laufvariable festlegen
    element* book_prev = book;


    if(first == NULL){                                      //Fall: die Liste ist leer - new_elem ist er erste Eintrag
        return(new_elem);
    }


    if(first->isbn > new_elem->isbn) {                      //Fall: new_elem ist kleiner als der erste Eintrag
        new_elem->next = first;                             //und muss somit an die erste Stelle
        return(new_elem);
    }

    while((book != NULL)){
        if (book->next == NULL){                            //Vergleich mit dem letzten Eintrag in der Liste

            if(book->isbn > new_elem->isbn) {               //Fall: new_elem kleiner als letzter Eintrag
                new_elem->next = book;
                book_prev->next = new_elem;
            } else {                                        //Fall: new_elem größer als letzter Eintrag
                book->next = new_elem;
            }
            break;
        }

        if (book->next && book->next->isbn > new_elem->isbn) {  //Fall: einfügen in der Mitte
            new_elem->next = book->next;
            book->next = new_elem;
            break;
        }
        book_prev = book;
        book = book->next;
    }
    return(first);
    //return(book);
}

/* Kreiere ein neues Element mit dynamischem Speicher.
 *
 * title  - Titel des Buches
 * author - Autor des Buches
 * year   - Erscheinungsjahr des Buches
 * isbn   - ISBN des Buches
 *
 * Gib einen Pointer auf das neue Element zurueck.
 */
element *construct_element(char *title, char* author, int year, long long int isbn) {
    /* HIER implementieren. */
    //einzelne Werte werden dem neuen Element zugewiesen
    element * new;
    new = (element *) calloc(1, sizeof(element));
    strncpy(new->title, title, MAX_STR-1);
    strncpy(new->author, author, MAX_STR-1);
    //new->title[MAX_STR-1] = '\0';
    //new->author[MAX_STR-1] = '\0';
    new->year = year;
    new->isbn = isbn;
    return(new);
}

/* Gib den der Liste und all ihrer Elemente zugewiesenen
 * Speicher frei.
 */
void free_list(list *alist) {
    /* HIER implementieren. */
    element* misc = alist -> first;              //Laufvariable festlegen
    while(misc != NULL){                         //Durchlaufen der Liste
        element* misc_next = misc -> next;
        free(misc);
        misc = misc_next;
    }
    free(alist);                                 //freigeben der Liste
}

/* Lese die Datei ein und fuege neue Elemente in die Liste ein 
 * _Soll nicht angepasst werden_
 */
void read_list(char* filename, list *alist) {
    element* new_elem;
    char* title;
    char* author;
    int year;
    long long int isbn;
    read_line_context ctx;
    open_file(&ctx, filename);
    while(read_line(&ctx, &title, &author, &year, &isbn) == 0) {
        new_elem = construct_element(title, author, year, isbn);
        alist->first = insert_sorted(alist->first, new_elem);
        alist->count++;
    }
}

/* Erstelle die Liste:
 *  - Weise ihr dynamischen Speicher zu 
 *  - Initialisiere die enthaltenen Variablen
 * _Soll nicht angepasst werden_
 */
list* construct_list() {
    list *alist = malloc(sizeof(list));
    alist->first = NULL;
    alist->count = 0;
    return alist;
}

/* Gib die Liste aus:
 * _Soll nicht angepasst werden_
 */
void print_list(list *alist) {
    printf("Meine Bibliothek\n================\n\n");
    int counter = 1;
    element *elem = alist->first;
    while (elem != NULL) {
        printf("Buch %d\n", counter);
        printf("\tTitel: %s\n", elem->title);
        printf("\tAutor: %s\n", elem->author);
        printf("\tJahr:  %d\n", elem->year);
        printf("\tISBN:  %lld\n", elem->isbn);
        elem = elem->next;
        counter++;
    }
}

/* Main Funktion
 * _Soll nicht angepasst werden_
 */
int main(int argc, char** argv) {
    list *alist = construct_list();
    read_list(argc>1?argv[1]:"buecherliste.txt", alist);
    print_list(alist);
    free_list(alist);
    return 0;
}
