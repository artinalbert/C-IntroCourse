/*
Zur Abgabe einen branch `iprg-b06` erstellen und pushen, in dem als einzige Datei die `06ex.c` liegt.
*/

/*
Um die Tests für dieses Blatt zu kompilieren und zu starten, führen Sie den folgenden Befehl aus:
cc -std=c11 -g -Wall -Werror 06ex_test.c -o 06ex_test.o -lm && ./06ex_test.o

Wir empfehlen, mit möglichst streng eingestelltem valgrind zu testen, denn so testen wir auch auf dem Server:
cc -std=c11 -g -Wall -Werror 06ex_test.c -o 06ex_test.o -lm && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./06ex_test.o
*/

#include "array_visualizer.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
void printArray(uint8_t *arr, size_t len)
{
    const char *s2 = format_uint8_array(arr, len);
    printf("%s", s2);
    free((char *)s2);
}
uint8_t *manipulator(uint8_t *arr, size_t len)
{
    // create an array with the sae size
    // stack(bound to the scope) vs  - heap(shared - with malloc - should be freed):

    uint8_t *newArr = malloc(len * sizeof(uint8_t));

    if (newArr == NULL)
    {
        // Handle memory allocation failure
    }
    newArr[len - 1] = arr[0];
    for (size_t i = 0; i < (len - 1); i++)
    {
        newArr[i] = arr[i + 1];
    }
    return newArr;
}

/*
Aufgabe 1:
Machen Sie sich in dieser Aufgabe mit dem `Visualizer` (siehe array_visualizer.h) vertraut.
Nutzen Sie die `visualizer_append_array` Funktion damit die Tests durchlaufen.

Tipp 1: Die erste Zeile im erzeugten Bild stellt das Eingabearray dar.
*/
void warmup(Visualizer *v, uint8_t *arr, size_t len)
{
    uint8_t *temp;
    for (size_t i = 1; i < 13; i++)
    {
        visualizer_append_array(v, arr);

        temp = manipulator(arr, len); // Manipulate the array and store in temp
        if (temp != NULL)
        {
            if (i != 1)
            {
                free(arr); // Free the previous arr, except for the first iteration
            }
            arr = temp; // Update arr to point to the newly allocated array
        }

        printArray(arr, len);
    }

    free(arr); // Free the last allocated array
}
/*
Aufgabe 2:
Bringen Sie die Tests zum durchlaufen.

Tipp 1: Die erste Zeile im erzeugten Bild stellt das Eingabearray dar.
Tipp 2: Es handelt sich um eine Abwandlung von iterativem Mergesort.
Tipp 3: `len` ist immer eine Dreierpotenz, damit Sie sich nicht mit Rundungsdetails herumschlagen brauchen.
*/
void sort_it(Visualizer *v, uint8_t *arr, size_t len)
{
}
