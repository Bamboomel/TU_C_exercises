#include <stdlib.h>
#include <stdio.h>	// Ein- / Ausgabe
#include <math.h>	// Für die Berechnungen der Ausgabe
#include "avl.h"

//max Funktion
int max(int a, int b){
    if(a > b){
        return a;
    }

    return b;
}

/* Gibt den gesamten AVL Baum in "in-order" Reihenfolge aus. */
void AVL_in_order_walk(AVLTree* avlt)
{
    AVLNode* x = avlt->root;
    if (x != NULL){
        AVL_in_order_walk(x->left);
    }
    AVL_in_order_walk(x->right);
}

/* Diese Funktion führt eine Linksrotation auf dem angegebenen
 * Knoten aus.
 *
 * Beachtet: Die Höhen der entsprechenden Teilbäume müssen (lokal)
 * angepasst werden.  Falls dies nicht eingehalten wird
 * funktionieren die Unit-Tests ggf. nicht.
 */
void AVL_rotate_left(AVLTree* avlt, AVLNode* x)
{
    AVLNode *y = x->right;
    x->right = y->left;

    if(y->left != NULL){
        y->left->parent = x;
    }

    y->parent = x->parent;

    if(x->parent == NULL){
        avlt->root = y;
    }else if(x == x->parent->left){
        x->parent->left = y;
    }else{
        x->parent->right = y;
    }

    y->left = x;
    x->parent = y;

}

/* Diese Funktion führt eine Rechtsrotation auf dem angegebenen
 * Knoten aus.
 *
 * Beachtet: Die Höhen der entsprechenden Teilbäume müssen (lokal)
 * angepasst werden.  Falls dies nicht eingehalten wird
 * funktionieren die Unit-Tests ggf. nicht.
 */
void AVL_rotate_right(AVLTree* avlt, AVLNode* y)
{
    AVLNode *x = y->right;
    y->right = x->left;

    if(x->left != NULL){
        x->left->parent = y;
    }

    x->parent = y->parent;

    if(y->parent == NULL){
        avlt->root = x;
    }else if(y == y->parent->left){
        y->parent->left = x;
    }else{
        y->parent->right = x;
    }

    x->left = y;
    y->parent = x;
}

/* Balanciere den Teilbaum unterhalb von node.
 *
 * Beachtet: Die Höhen der entsprechenden Teilbäume müssen _nicht_
 * angepasst werden, da dieses schon in den Rotationen geschieht.
 * Falls dies nicht eingehalten wird funktionieren die Unit-Tests
 * ggf. nicht.
 */
void AVL_balance(AVLTree* avlt, AVLNode* node)
{
    if(node->left->height > (node->right->height +1)){
        if(node->left->left->height < node->left->right->height){
            AVL_rotate_left(avlt, node->left);
        }
        AVL_rotate_right(avlt,  node);
    }else if(node->right->height > node->left->height){
        if(node->right->right->height < node->right->left->height){
            AVL_rotate_right(avlt, node->right);
        }
        AVL_rotate_left(avlt, node);
    }

}

//Hilfsfunktion
int check_height(AVLNode* node){
    if(node == NULL){
        return 0;
    }

    return node->height;
}



void AVL_insert_value_node(AVLTree* avlt, AVLNode* old_node, int value)
{
    AVLNode *new_node;
    new_node = (AVLNode *) malloc(1 * sizeof(AVLNode));
    new_node->parent = NULL;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->value = value;
    new_node->height = 1;

    if(old_node == NULL){
        return;
    }
    else if(value < old_node->value){
        printf("Test Zeile 135\n");
        AVL_insert_value_node(avlt, old_node->left, value);
    }
    else if(value > old_node->value){
        printf("Test Zeile 139\n");
        AVL_insert_value_node(avlt, old_node->right, value);
    }
    else{
        printf("Test Zeile 144\n");
        return; //Schlüssel bereits vorhanden
    }

    avlt->numberOfNodes++;
    old_node->height = 1 + max(check_height(old_node->left), check_height(old_node->right));
    AVL_balance(avlt, old_node);
}

/* Fügt der Wert value in den Baum ein.
 *
 * Die Implementierung muss sicherstellen, dass der Baum nach dem
 * Einfügen immer noch balanciert ist!
 */
void AVL_insert_value(AVLTree* avlt, int value)
{
    AVLNode *node;
    node = (AVLNode *) malloc(1 * sizeof(AVLNode));
    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;
    node->value = value;
    node->height = 1;

    if (avlt->root == NULL){
        avlt->root = node;
        printf("Test Zeile 165\n");
        avlt->numberOfNodes++;
        printf("Test Zeile 167\n");
        return;
    }
    else{
        printf("Test Zeile 171\n");
        AVLNode *old_node = avlt->root;
        printf("Test Zeile 173\n");
        if(node == NULL){
            return;
        }
        else if(node->value < old_node->value){
            printf("Test Zeile 175\n");
            AVL_insert_value_node(avlt, old_node->left, value);
        }
        else if(node->value > old_node->value){
            printf("Test Zeile 179\n");
            AVL_insert_value_node(avlt, old_node->right, value);
        }
        else{
            return; //Schlüssel bereits vorhanden
        }

        node->height = 1 + max(check_height(node->left), check_height(node->right));
        AVL_balance(avlt, node);
    }
}


/* Löscht den gesamten AVL-Baum und gibt den Speicher aller Knoten
 * frei.
 */
void AVL_remove_all_elements(AVLTree* avlt)
{
    AVLNode* node = avlt;

    if(node == NULL){
        return;
    }

    if(node != NULL){
        free(node->value);
        AVL_remove_all_elements(node->left);
        AVL_remove_all_elements(node->right);
        free(node);
    }
    // Hier Code implementieren!
}
