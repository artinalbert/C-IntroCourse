/*
Zur Abgabe einen branch `iprg-b05` erstellen und pushen, in dem als einzige Datei die `05ex.c` liegt.
*/

/*
Um die Tests für dieses Blatt zu kompilieren und zu starten, führen Sie den folgenden Befehl aus:
cc -std=c11 -g -Wall -Werror 05ex_test.c -o 05ex_test.o -lm && ./05ex_test.o

Wir empfehlen, mit möglichst streng eingestelltem valgrind zu testen, denn so testen wir auch auf dem Server:
cc -std=c11 -g -Wall -Werror 05ex_test.c -o 05ex_test.o -lm && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./05ex_test.o
*/

#include "search_tree.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/*
Aufgabe 1:

Fügen Sie den Wert `x` als Blatt so in den nicht-leeren Suchbaum `t` ein, dass `t` hinterher
wieder ein Suchbaum ist. Falls `x` bereits in `t` vorkam, soll `t` stattdessen
unverändert bleiben.
Geben Sie zurück, ob der Baum modifiziert wurde.

Nutzen Sie `malloc`, um das neue Blatt zu erstellen. Der Testrunner wird das Blatt wieder `free`n,
darum brauchen Sie sich nicht zu kümmern.
*/
//node : double pointer to a TreeNode
bool insert_node(TreeNode **node, uint16_t x) {

    //das aktuelle Element ein Null-Pointer ist
    if (*node == NULL) {
        // Erstelle einen neuen Knoten, wenn das aktuelle Element ein Null-Pointer ist
        //malloc with casted output
        *node = (TreeNode *)malloc(sizeof(TreeNode));
        if (*node == NULL) {
            // Speicherallokation fehlgeschlagen
            return false;
        }
        //-> to dereference(?)
        (*node)->item = x;
        (*node)->left = NULL;
        (*node)->right = NULL;
        return true;
    } else if (x < (*node)->item) {
        // Gehe zum linken Kind, wenn x kleiner ist als der aktuelle Knoten
        //& opposite of dereferencing -- gets us a double pointer
        return insert_node(&((*node)->left), x);
    } else if (x > (*node)->item) {
        // Gehe zum rechten Kind, wenn x größer ist als der aktuelle Knoten
        return insert_node(&((*node)->right), x);
    } else {
        // x ist bereits im Baum, keine Änderung
        return false;
    }
}
bool search_tree_insert(TreeNode *t, uint16_t x) {
       if (t == NULL) {
        return false; // Der Baum ist leer
    }
    return insert_node(&t, x);
}

/*
Aufgabe 2:
Geben Sie die kleinste Zahl im Suchbaum `t` zurück, welche echt größer als `x` ist.
Falls keine solche Zahl existiert, geben Sie stattdessen `x` zurück. Die Laufzeit Ihrer Lösung soll
proportional zur Höhe des Baumes sein, aber unabhängig von der Gesamtzahl an Knoten.
*/
uint16_t search_tree_get_greater_than(TreeNode *t, uint16_t x) {
    uint16_t minGreater = x;
    while (t != NULL) {
        if (t->item > x) {
            minGreater = t->item; // Aktualisiere minGreater, falls ein größerer Wert gefunden wird
            t = t->left; // Es könnte einen noch kleineren Wert geben, der größer als x ist, also nach links
        } else {
            t = t->right; // Der aktuelle Knotenwert und alle Werte im linken Teilbaum sind nicht größer als x, also nach rechts
        }
    }
    return minGreater;
}
