#ifndef HEAP_H
#define HEAP_H

#include "data_structures.h"

void buildHeap(HEAP *pHeap, ELEMENT **V, int n);
void insert(HEAP *pHeap, ELEMENT **V, int index);
ELEMENT* extractMin(HEAP *pHeap, ELEMENT **V);
void decreaseKey(HEAP *pHeap, ELEMENT **V, int index, double newKey);
void printHeap(HEAP *pHeap, ELEMENT **V);
void printArray(TAG_ELEMENT **V, int n);

#endif
