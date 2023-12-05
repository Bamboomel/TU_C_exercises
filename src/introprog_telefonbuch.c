#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "introprog_telefonbuch.h"

void bst_free_node(bst_node* node) {
    if(node != NULL){
        free(node->name);
        bst_free_node(node->left);
        bst_free_node(node->right);
        free(node);
    }
}

/*
 * Fügt einen Knoten mit der Telefonnummer phone und dem Namen name
 * in den Binären Suchbaum bst ein.  Für den Suchbaum soll die
 * Eigenschaft gelten, dass alle linken Kinder einen Wert kleiner
 * gleich (<=) und alle rechten Kinder einen Wert größer (>) haben.
 */
void bst_insert_node(bstree* bst, unsigned long phone, char *name) {
    //new node
    bst_node *z;
    z = (bst_node *) malloc(1 * sizeof(bst_node));
    z->parent = NULL;
    z->left = NULL;
    z->right = NULL;
    z->name = NULL;
    z->phone = 0;

    //z->name = (char *) malloc((strlen(name) * sizeof(char)) + 1);
    if ( strlen(name) < MAX_STR) {
        z->name = (char *) malloc((strlen(name) + 1) * sizeof(char));

        for (int i = 0; i < strlen(name) + 1; i++) {
            z->name[i] = 0x00;
        }

        strncpy(z->name, name, strlen(name) + 1);

    } else {
        z->name = (char *) malloc(MAX_STR * sizeof(char));

        for (int i = 0; i < MAX_STR; i++) {
            z->name[i] = 0x00;
        }

        strncpy(z->name, name, MAX_STR);

    }


//    z->name = (char *) malloc(MAX_STR * sizeof(char));
//
//    for (int i = 0; i < MAX_STR; i++) {
//        z->name[i] = 0x00;
//    }
//
//    strcpy(z->name, name);
    //strncpy(z->name, name, strlen(name));
    //z->name = strdup(name);
    z->phone = phone;

    //Variablen zum Einfügen
    bst_node *y;
    bst_node *x;

    if (z->name != NULL) {
        if (strlen(z->name) == 0) {
            //printf("Name ist leer.\n");
            bst_free_node(z);
            return;
        }
    } else {
        bst_free_node(z);
    }

    if(!(z->phone >= 1) || !(z->phone <= 999999999)) {
        //printf("Telefonnummer %lu nicht gueltig.\n", z->phone);
        bst_free_node(z);
        return;
    }

    if (bst->root != NULL) {
        x = bst->root;
    } else {
        bst->root = z;
        bst->count++;
        return;
    }
    y = x;

    //while Schleife um zu prüfen in welchen child-branch wir uns bewegen wollen
    while (x != NULL) {

        y = x;
        if (z->phone < x->phone) {       //falls einzufügende Nummer größer als aktueller Knoten
            x = x->left;
        } else if (z->phone > x->phone){
            x = x->right;               //falls einzufügende Nummer kleiner als aktueller Knoten
        } else{
            printf("Telefonnummer %lu existiert bereits.\n", z->phone);
            bst_free_node(z);
            return;
        }
    }

    if (y == NULL) {                        //falls z keinen Elter hat
        bst->root = z;                      //z wird zum Elter
        bst->count++;
    } else {
        //z->parent = y;
        if (z->phone < y->phone) {
            y->left = z;
            bst->count++;
        } else if (z->phone > y->phone){
            y->right = z;
            bst->count++;
        }
    }
    //}
}

/*
 * Diese Funktion liefert einen Zeiger auf einen Knoten im Baum mit
 * dem Wert phone zurück, falls dieser existiert.  Ansonsten wird
 * NULL zurückgegeben.
 */
bst_node* find_node(bstree* bst, unsigned long phone) {
    //übergebene Nummer in z
    //bst_node *z;
    //z = malloc(1 * sizeof(bst_node));
    //z->phone = phone;

    bst_node *x = bst->root;

    if(x == NULL || ((x->phone < 1) || (x->phone > 999999999))){                          //Fall: Baum ist leer
        return NULL;
    }

    while(x != NULL){
        if(x->phone > phone){            //Fall: Knoten größer als übergebene Nummer
            x = x->left;
        }
        else if(x->phone < phone){        //Fall: Knoten kleiner als übergebene Nummer
            x = x->right;
        }
        else{
            return x;                       //Fall: Knoten entspricht der Nummer
        }
    }
    return x;                         //Fall: Nummer ist nicht im Baum


}

/* Gibt den Unterbaum von node in "in-order" Reihenfolge aus */
void bst_in_order_walk_node(bst_node* node) {

    if(node == NULL){
        return;
    }

    if(node != NULL){
        bst_in_order_walk_node(node->left);
    }
    print_node(node);
    bst_in_order_walk_node(node->right);

}

/* 
 * Gibt den gesamten Baum bst in "in-order" Reihenfolge aus.  Die
 * Ausgabe dieser Funktion muss aufsteigend soriert sein.
 */
void bst_in_order_walk(bstree* bst) {
    if (bst != NULL) {
        bst_in_order_walk_node(bst->root);
    }
}

/*
 * Löscht den Teilbaum unterhalb des Knotens node rekursiv durch
 * "post-order" Traversierung, d.h. zurerst wird der linke und dann
 * der rechte Teilbaum gelöscht.  Anschließend wird der übergebene
 * Knoten gelöscht.
 */
void bst_free_subtree(bst_node* node) {

    if(node == NULL){
        return;
    }

    if(node != NULL){
        free(node->name);
        bst_free_subtree(node->left);
        bst_free_subtree(node->right);
        free(node);
    }

    /*if(node == NULL){
        return;
    }

    bst_free_subtree(node->left);
    bst_free_subtree(node->right);
    free(node);
    */
}

/* 
 * Löscht den gesamten Baum bst und gibt den entsprechenden
 * Speicher frei.
 */
void bst_free_tree(bstree* bst) {
    if(bst != NULL && bst->root != NULL) {
        bst_free_subtree(bst->root);
        bst->root = NULL;
    }
}
