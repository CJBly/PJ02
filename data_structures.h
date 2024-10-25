#ifndef DATA_STRUCTURES_H
#define DTA_STRUCTURES_H

typedef struct TAG_ELEMENT{
    int index; // Index of the element
    double key; // Key value of element
    int pos; // index in the heap-array, 0 if not in the heap
// Other fields can be added
}ELEMENT;
    

typedef struct TAG_HEAP{
    int capacity; // capacity of the heap
    int size; // current size of the heap
    int *H; // array of pointers to indiced of the ELEMENT array
// Other fields can be added
}HEAP;

#endif
