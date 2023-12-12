#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "introprog_buecherliste.h"
#include "introprog_structs_lists_input.h"

// Insert an element at the beginning of the list
element* insert_at_begin(element* head, element* new_element) {
    new_element->next = head;
    return new_element;
}

// Create a new element with dynamic memory
element *construct_element(const char* title, const char* author, uint32_t year, uint64_t isbn) {
    element *new_element = (element*) calloc(1, sizeof(element));
    if (new_element == NULL) {
        perror("Failed to allocate memory for new element");
        exit(EXIT_FAILURE);
    }
    snprintf(new_element->title, MAX_STR, "%s", title);
    snprintf(new_element->author, MAX_STR, "%s", author);
    new_element->year = year;
    new_element->isbn = isbn;
    new_element->next = NULL;
    return new_element;
}

// Free the memory allocated for the list and its elements
void free_list(list* book_list) {
    element *current;
    while(book_list->count != 0) {
        current = book_list->first;
        book_list->first = current->next;
        free(current);
        book_list->count--;
    }
    free(book_list);
}

// Read the file and add new elements to the list
void read_list(char* filename, list* book_list) {
    element* new_element;

    char* new_title;
    char* new_author;
    uint32_t new_year;
    uint64_t new_isbn;
    read_line_context ctx;
    open_file(&ctx, filename);
    while(read_line(&ctx, &new_title, &new_author, &new_year, &new_isbn) == 0) {
        new_element = construct_element(new_title, new_author, new_year, new_isbn);
        book_list->first = insert_at_begin(book_list->first, new_element);
        book_list->count++;
    }
}

// Create and initialize the list
list* construct_list() {
    list *book_list = malloc(sizeof(list));
    if (book_list == NULL) {
        perror("Failed to allocate memory for list");
        exit(EXIT_FAILURE);
    }
    book_list->first = NULL;
    book_list->count = 0;
    return book_list;
}
