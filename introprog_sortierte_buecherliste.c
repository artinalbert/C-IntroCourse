#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "introprog_sortierte_buecherliste.h"
#include "introprog_structs_lists_input.h"
#include "introprog_buecherliste.h"

/* Insert an element into the list in ascending order based on ISBN */
element* insert_sorted(element* head, element* new_element) {
    if (head == NULL || new_element->isbn < head->isbn) {
        new_element->next = head;
        return new_element;
    }

    element* current = head;
    while (current->next != NULL && current->next->isbn < new_element->isbn) {
        current = current->next;
    }

    new_element->next = current->next;
    current->next = new_element;
    return head;
}

/* Read the file and insert new elements into the list in sorted order */
void read_list_sorted(char* filename, list *book_list) {
    element* new_element;
    char* title;
    char* author;
    uint32_t year;
    uint64_t isbn;
    read_line_context ctx;

    open_file(&ctx, filename);
    while (read_line(&ctx, &title, &author, &year, &isbn) == 0) {
        new_element = construct_element(title, author, year, isbn);
        book_list->first = insert_sorted(book_list->first, new_element);
        book_list->count++;
    }
}