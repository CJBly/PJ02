#ifndef HEAP_H
#define HEAP_H

#include "data_structures.h"

void buildHeap(HEAP *pHeap, ELEMENT **V, int n);
void insert(HEAP *pHeap, ELEMENT **V, int Index);
ELEMENT* extractMin(HEAP *pHeap, ELEMENT **V);
void decreaseKey(HEAP *pHeap, ELEMENT **V, int Index, double Key);
void printHeap(HEAP *pHeap, ELEMENT **V);

#endif
