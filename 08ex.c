/*
Zur Abgabe einen branch `iprg-b08` erstellen und pushen, in dem als einzige Datei die `08ex.c` liegt.
*/

/*
Um die Tests für dieses Blatt zu kompilieren und zu starten, führen Sie den folgenden Befehl aus:
cc -std=c11 -g -Wall -Werror 08ex_test.c -o 08ex_test.o -lm && ./08ex_test.o

Wir empfehlen, mit möglichst streng eingestelltem valgrind zu testen, denn so testen wir auch auf dem Server:
cc -std=c11 -g -Wall -Werror 08ex_test.c -o 08ex_test.o -lm && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./08ex_test.o
*/

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/* Ein Array zusammen mit seiner Länge. */
typedef struct ArrayWithLength_ {
    uint16_t *arr;
    size_t len;
} ArrayWithLength;

/*
Bei merge sort werden häufiger mal *zwei* vorsortierte Arrays kombiniert. Auf diesem Blatt
kombinieren wir effizient *beliebig viele* vorsortierte Arrays mit einem divide-and-conquer Algorithmus.
*/

/*
Aufgabe 1a:

Gegeben ein absteigend sortiertes Array, geben Sie ein absteigend sortiertes Array
mit den gleichen Elementen zurück.
Der Speicher für die Arrayelemente im Rückgabewert soll eigens mit malloc allokiert werden.

Tipp: Ja, es ist wirklich so banal wie es klingt. Das haben base-cases bei divide-and-conquer
Algorithmen häufig so an sich.
*/
ArrayWithLength base_case(ArrayWithLength arr) {
    ArrayWithLength ret;
    ret.arr = (uint16_t *)malloc(sizeof(uint16_t) * arr.len);
    ret.len = arr.len;

    for(size_t i = 0; i < arr.len; i++) {
        ret.arr[i] = arr.arr[i];
    }

    return ret;
}

/*
Aufgabe 1b:

Gegeben zwei absteigend sortierte Arrays der Längen len1 und len2,
geben Sie ein absteigend sortiertes Array zurück,
welches die Elemente beider Eingabearrays enthält. Die Funktion soll in O(len1 + len2) laufen.
Der Speicher für die Arrayelemente im Rückgabewert soll eigens mit malloc allokiert werden.
*/
ArrayWithLength combine(ArrayWithLength arr1, ArrayWithLength arr2) {
    ArrayWithLength ret;
    ret.arr = (uint16_t *)malloc(sizeof(uint16_t) * (arr1.len + arr2.len));
    ret.len = arr1.len + arr2.len;

    size_t i = 0, j = 0, k = 0;
    while(i < arr1.len && j < arr2.len) {
        if(arr1.arr[i] > arr2.arr[j]) {
            ret.arr[k++] = arr1.arr[i++];
        } else {
            ret.arr[k++] = arr2.arr[j++];
        }
    }

    while(i < arr1.len) {
        ret.arr[k++] = arr1.arr[i++];
    }

    while(j < arr2.len) {
        ret.arr[k++] = arr2.arr[j++];
    }

    return ret;
}

/*
Aufgabe 1c:

Gegeben ein nichtleeres Array `arrs` aus `count` vielen absteigend sortierten Arrays, geben Sie ein absteigend sortiertes Array
zurück, welches die Elemente aller Eingabearrays enthält. Ihre Lösung soll in O(n * log(count)) laufen, wobei `n` die
Gesamtzahl an Elementen in allen Arrays ist. Dazu müssen sie clever dive-and-conquern.

Der Speicher für die Arrayelemente im Rückgabewert soll eigens mit malloc allokiert werden.
*/
ArrayWithLength merge_k(ArrayWithLength *arrs, size_t count) {
    if(count == 1) {
        return base_case(arrs[0]);
    }

    size_t mid = count / 2;
    ArrayWithLength left = merge_k(arrs, mid);
    ArrayWithLength right = merge_k(arrs + mid, count - mid);

    ArrayWithLength merged = combine(left, right);

    free(left.arr);
    free(right.arr);

    return merged;
}