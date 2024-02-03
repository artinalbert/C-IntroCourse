/*
Zur Abgabe einen branch `iprg-b09` erstellen und pushen, in dem als einzige Datei die `09ex.c` liegt.
*/

/*
Um die Tests für dieses Blatt zu kompilieren und zu starten, führen Sie den folgenden Befehl aus:
cc -std=c11 -g -Wall -Werror 09ex_test.c -o 09ex_test.o -lm && ./09ex_test.o

Wir empfehlen, mit möglichst streng eingestelltem valgrind zu testen, denn so testen wir auch auf dem Server:
cc -std=c11 -g -Wall -Werror 09ex_test.c -o 09ex_test.o -lm && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./09ex_test.o
*/

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "tree.h"
#include "array.h"

/*
Aufgabe 1:

Gegeben ein Array `arr`, geben Sie zurück, ob der zugehörige linksvollständige Binärbaum
die max-heap Eigenschaft erfüllt.
*/
bool is_max_heap(Array arr)
{

    // Behandle den Fall eines leeren Arrays als gültigen Max-Heap
    if (arr.len < 2)
    {
        // returning early > no need for else
        return true;
        // arr.len is unsigned short! >> can not be negative - underflow
    }
    for (size_t i = 0; i <= (arr.len - 2) / 2; i++)
    {
        // Überprüfe, ob das aktuelle Element kleiner als sein linkes Kind ist
        if (arr.arr[i] < arr.arr[2 * i + 1])
        {
            return false;
        }
        // Überprüfe, ob das aktuelle Element kleiner als sein rechtes Kind ist,
        // falls das rechte Kind existiert
        if (2 * i + 2 < arr.len && arr.arr[i] < arr.arr[2 * i + 2])
        {
            return false;
        }
    }
    return true;
}
void insert_into_array(TreeNode *node, uint16_t *array, size_t position)
{
    if (node == NULL)
    {
        return; // Basisfall: Wenn der Knoten null ist, tue nichts.
    }

    // Füge den Wert des aktuellen Knotens an der berechneten Position ins Array ein.
    array[position] = node->item;

    // Rekursive Aufrufe für das linke und das rechte Kind, wenn sie existieren.
    // Berechne die Positionen für die Kinder und rufe die Funktion rekursiv auf.
    if (node->left != NULL)
    {
        insert_into_array(node->left, array, 2 * position + 1);
    }
    if (node->right != NULL)
    {
        insert_into_array(node->right, array, 2 * position + 2);
    }
}
/*
Aufgabe 2:

Gegeben ein linksvollständiger Binärbaum, tragen Sie im Array `arr` dessen Arrayrepräsentation ein.

Tipp 1: Wie so häufig bei Bäumen, bietet sich hier eine rekursive Lösung an.
Tipp 2: Diese Funktion selbst ist allerdings nur so mäßig gut für rekursive Aufrufe geeignet, eventuell sollten Sie sich eine (rekursive) Hilfsfunktion schreiben.
Tipp 3: Die Position eines Knotens im Array lässt sich relativ leicht bestimmen, wenn man die Position vom Elternknoten weiß, und, ob es sich um ein linkes oder ein rechtes Kind handelt.
Tipp 4: Ja, das sind also sinnvolle Argumente für die Hilfsfunktion.
Tipp 5: Regelmäßig zähneputzen und genug bewegen.
*/
void tree_to_array(TreeNode *t, Array arr)
{
    // bfs - level order traversal
    // queue
    //  TreeNode *queue[arr.len];
    //  int front = 0;
    //  int rear = 0;
    //  queue[rear++] = t;
    //  while (front < rear) {
    //      TreeNode *node = queue[front++];
    //      if (node != NULL) {
    //          arr.arr[arr.len++] = node->item;
    //          queue[rear++] = node->left;
    //          queue[rear++] = node->right;
    //      }
    //  }

    if (t == NULL || arr.arr == NULL)
    {
        return; // Sicherstellen, dass weder der Baum noch das Array null sind.
    }

    // Starte den rekursiven Prozess mit der Wurzel des Baums und der Position 0 im Array.
    insert_into_array(t, arr.arr, 0);
}
