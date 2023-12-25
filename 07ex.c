/*
Zur Abgabe einen branch `iprg-b07` erstellen und pushen, in dem als einzige Datei die `07ex.c` liegt.
*/

/*
Um die Tests für dieses Blatt zu kompilieren und zu starten, führen Sie den folgenden Befehl aus:
cc -std=c11 -g -Wall -Werror 07ex_test.c -o 07ex_test.o -lm && ./07ex_test.o

Wir empfehlen, mit möglichst streng eingestelltem valgrind zu testen, denn so testen wir auch auf dem Server:
cc -std=c11 -g -Wall -Werror 07ex_test.c -o 07ex_test.o -lm && valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./07ex_test.o
*/

#include "sphinx.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/*
Aufgabe 1:

Da spaziert man entspannt durch Theben, und plötzlich kommt eine Sphinx angeflogen
und spricht: "Ich habe mir ein Array mit n absteigend sortierten Zahlen überlegt (Zahlen
können mehrfach vorkommen). Du darfst mich nach dem Wert an 1 + log2(n) (aufgerundet) vielen
Positionen fragen. Und wenn du mir danach nicht sagen kannst, ob das Array die Zahl 12345
enthält, dann fresse ich dich.".

Geben Sie zurück, ob das Array der Sphinx die Zahl 12345 enthält. Um den Wert an Position `i`
zu erfragen, rufen Sie `sphinx_ask(s, i)` auf. Aber Achtung: Wenn Sie diese Funktion mehr als
1 + log2(n) (aufgerundet) mal aufrufen, stürzt das Programm fehlerhaft ab.
*/
// bool descending_sphinx(Sphinx *s, size_t n)
// {
//     if (n == 0)
//     {
//         return false;
//     }
//     uint16_t valueToCompare = sphinx_ask(s, 0);
//     if (valueToCompare == 12345)
//     {
//         return true;
//     }
//     uint16_t originalSize = n;
//     n /= 2;
//     while (n > 1)
//     {
//     uint16_t valueToCompare = sphinx_ask(s, n);
//         printf("%zu %d\n", n, valueToCompare);
//         if (valueToCompare == 12345)
//         {
//             return true;
//         }
//         if (valueToCompare > 12345)
//         {
//             n = (n + originalSize) / 2;
//             // n = n + originalSize / 2;
//             //  n += n / 2;
//             printf("%zu %d\n", n, valueToCompare);
//         }
//         if (valueToCompare < 12345)
//         {
//             n /= 2;
//             printf("%zu %d\n", n, valueToCompare);
//         }
//     }

//     return false;
// }
// bool descending_sphinx(Sphinx *s, size_t n)
// {
//     size_t upperBound = n - 1;
//     size_t lowerBound = 0;

//     if (n == 0)
//     {
//         return false;
//     }
//     while (upperBound - lowerBound > 1)
//     {
//         size_t middleIdx = lowerBound + (upperBound - lowerBound) / 2;
//         uint16_t valueToCompare = (s,middleIdx);
//         if (valueToCompare == 12345)
//         {
//             return true;
//         }
//         if (valueToCompare > 12345)
//         {
//         lowerBound = middleIdx;
//         }
//         if (valueToCompare < 12345)
//         {
//            upperBound = middleIdx;
//         }
//     }
//     return false;
// }
bool descending_sphinx(Sphinx *s, size_t n)
{
    size_t upperBound = n;
    size_t lowerBound = 0;

    if (n == 0)
    {
        return false;
    }
    if (n == 1 && sphinx_ask(s, 0) == 12345)
    {
        return true;
    }
    while (upperBound - 1 != lowerBound)
    {
        size_t middleIdx = lowerBound + (upperBound - lowerBound) / 2;
        printf("%zu ", lowerBound);
        printf("%zu\n", upperBound);
        uint16_t valueToCompare = sphinx_ask(s, middleIdx);
        if (valueToCompare == 12345)
        {
            return true;
        }
        else if (valueToCompare > 12345)
        {
            lowerBound = middleIdx;
        }
        else
        {
            upperBound = middleIdx;
        }
    }
    return false;
}
