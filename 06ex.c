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

int getExponentBase3(int number)
{
    int exponent = 0;
    while (number % 3 == 0)
    {
        number /= 3;
        exponent++;
    }
    return exponent;
}

uint8_t *mergeSortIntoNewArray(int arrayLength, uint8_t *arrA, uint8_t *arrB, uint8_t *arrC)
{
    // Allocate memory for the new array
    uint8_t *result = calloc(arrayLength * 3 ,sizeof(uint8_t));
    if (result == NULL)
    {
        // Handle memory allocation failure if needed
        return NULL;
    }

    int i = 0, j = 0, k = 0, l = 0;

    // Merge arrays into result
    while (i < arrayLength || j < arrayLength || k < arrayLength)
    {
        // Assume the next element is the maximum possible value for uint8_t - 255
        uint8_t nextVal = 0xFF;

        // Find the next smallest element from the arrays
        if (i < arrayLength && arrA[i] < nextVal)
        {
            nextVal = arrA[i];
        }
        if (j < arrayLength && arrB[j] < nextVal)
        {
            nextVal = arrB[j];
        }
        // if(arrC[k] == 0){
        //     printf("%d",k);
        //     exit(-1);
        // }
        if (k < arrayLength && arrC[k] < nextVal)
        {
            nextVal = arrC[k];
        }

        // Add the smallest element to the result array
        result[l++] = nextVal;

        // Increment the pointer for the array from which the element was taken
        //to not increment two counters - we use else if instead of ifs -- to not lose values(some values will not be compared! - as only
        //one value was copied to nextVal)
        if (i < arrayLength && arrA[i] == nextVal)
            i++;
        else if (j < arrayLength && arrB[j] == nextVal)
            j++;
        else if (k < arrayLength && arrC[k] == nextVal)
            k++;
    }

    return result;
}

size_t min(size_t a, size_t b)
{
    return (a < b) ? a : b;
}
/*
sorts partial arrays of size subArrayLength within arr by iteratively calling merge sort into new arrays
*/
void partialSorter(Visualizer *v, uint8_t *arr, size_t arr_len, uint8_t subArrayLength)
{
    // Temporary array for merging
    // uint8_t *temp = malloc(arr_len * sizeof(uint8_t));
    // if (temp == NULL)
    // {
    //     // Handle memory allocation failure if needed
    //     return;
    // }

    // Start merging from the given subArrayLength

        for (size_t i = 0; i < arr_len; i += subArrayLength * 3)
        {
            // Calculate the lengths of the subarrays
            size_t length1 = min(subArrayLength, arr_len - i);
            size_t length2 = min(subArrayLength, arr_len - i - length1);
            size_t length3 = min(subArrayLength, arr_len - i - length1 - length2);

            if(length1!=length2|| length2!=length3){
                printf("%ld,%ld,%ld",length1,length2,length3);
                exit(-1);
            }
            printf("%ld",i);
            // Merge the subarrays
            uint8_t *merged = mergeSortIntoNewArray(subArrayLength, arr + i, arr + i + length1, arr + i + length1 + length2);

            // Copy the merged array back and free the allocated memory
            //memcpy(temp + i, merged, length1 + length2 + length3);
            memcpy(arr + i, merged, length1 + length2 + length3);
            free(merged);
            visualizer_append_array(v, arr);
        }
        //memcpy(arr, temp, arr_len);


    //free(temp);
}



void iterateOverStages(Visualizer *v, uint8_t *arr, size_t len) {
    int exponent = getExponentBase3(len);
    uint8_t subArrayLength = 1; // Start with the smallest unit

    for (int i = 0; i < exponent; i++) {
        partialSorter(v, arr, len, subArrayLength);

        // Increase the subArrayLength for the next stage
        subArrayLength *= 3;
    }
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
    // Initial sort of atomic triplets
    visualizer_append_array(v, arr); // Visualize after sorting triplets
    iterateOverStages(v,arr,len);
}

// /*
// sorts elements in groups equal to power of 3
// */
// uint8_t *trioSorter(uint8_t *arr, size_t len){

// }