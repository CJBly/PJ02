#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

// Swap helper function
void swap(ELEMENT **V, int *H, int a, int b) {
    int tempIndex = H[a];
    H[a] = H[b];
    H[b] = tempIndex;
    
    V[H[a]]->pos = a;
    V[H[b]]->pos = b;
}

// Heapify function to maintain the min-heap property
void heapify(HEAP *pHeap, ELEMENT **V, int index) {
    int smallest = index;
    int left = 2 * index;
    int right = 2 * index + 1;

    if (left <= pHeap->size && V[pHeap->H[left]]->key < V[pHeap->H[smallest]]->key)
        smallest = left;
    if (right <= pHeap->size && V[pHeap->H[right]]->key < V[pHeap->H[smallest]]->key)
        smallest = right;

    if (smallest != index) {
        swap(V, pHeap->H, index, smallest);
        heapify(pHeap, V, smallest);
    }
}

// Build heap function to convert an unsorted array into a min-heap
void buildHeap(HEAP *pHeap, ELEMENT **V, int n) {
    pHeap->size = n;
    for (int i = 1; i <= n; i++) {
        V[i]->pos = i;
        pHeap->H[i] = i;
    }
    for (int i = n / 2; i >= 1; i--) {
        heapify(pHeap, V, i);
    }
}

// Insert a new element into the heap
void insert(HEAP *pHeap, ELEMENT **V, int index) {
    if (pHeap->size >= pHeap->capacity) {
        fprintf(stderr, "Error: Heap capacity exceeded\n");
        return;
    }

    pHeap->size++;
    pHeap->H[pHeap->size] = index;
    V[index]->pos = pHeap->size;

    int i = pHeap->size;
    while (i > 1 && V[pHeap->H[i / 2]]->key > V[pHeap->H[i]]->key) {
        swap(V, pHeap->H, i / 2, i);
        i /= 2;
    }
}

// Extract the minimum element from the heap
ELEMENT* extractMin(HEAP *pHeap, ELEMENT **V) {
    if (pHeap->size == 0) {
        fprintf(stderr, "Error: Heap is empty\n");
        return NULL;
    }

    ELEMENT *minElement = V[pHeap->H[1]];
    pHeap->H[1] = pHeap->H[pHeap->size];
    V[pHeap->H[1]]->pos = 1;
    pHeap->size--;
    heapify(pHeap, V, 1);

    return minElement;
}

// Decrease the key of an element in the heap
void decreaseKey(HEAP *pHeap, ELEMENT **V, int index, double newKey) {
    if (V[index]->key < newKey) {
        fprintf(stderr, "Error: New key is larger than current key\n");
        return;
    }

    V[index]->key = newKey;
    int i = V[index]->pos;

    while (i > 1 && V[pHeap->H[i / 2]]->key > V[pHeap->H[i]]->key) {
        swap(V, pHeap->H, i / 2, i);
        i /= 2;
    }
}

// Print the elements of the heap
void printHeap(HEAP *pHeap, ELEMENT **V) {
    if (!pHeap) {
        fprintf(stderr, "Error: heap is NULL\n");
        return;
    }
    printf("Instruction: PrintHeap\n");
    printf("Capacity = %d, size = %d\n", pHeap->capacity, pHeap->size);
    
    // Print the contents of the heap
    for (int i = 1; i <= pHeap->size; i++) {
        printf("H[%d] = %d\n", i, pHeap->H[i]);
    }
}

void printArray(ELEMENT **V, int n) {
    if (!V) {
        fprintf(stderr, "Error: array is NULL\n");
        return;
    }
    printf("Instruction: PrintArray\n");
    for (int i = 1; i <= n; i++) {
        printf("%d %lf %d\n", V[i]->index, V[i]->key, V[i]->pos);
    }
}
