#include <stdint.h>
#ifndef MAX_STR
#define MAX_STR 255
#endif
#ifndef ELEMENT
#define ELEMENT
typedef struct _element {
    char title[MAX_STR];
    char author[MAX_STR];
    uint32_t year;
    uint64_t isbn;
    struct _element *next;
} element;
#endif
#ifndef LIST
#define LIST
typedef struct _list {
    element* first;
    int count;
} list;
#endif

#ifndef ELEMENTDEF
#define ELEMENTDEF

#endif

element* insert_at_begin(element* , element*);


element* construct_element(char*, char*, uint32_t, uint64_t);

void free_list(list*);


void read_list(char*, list*);

list* construct_list();