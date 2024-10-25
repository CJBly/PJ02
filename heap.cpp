#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

//Function to swap two elements in the heap
void swap(ELEMENT **V, int *H, int a, int b) {
    ELEMENT *temp = V[H[a]];
    V[H[a]] = V[H[b]];
    V[H[b]] = temp;

    int temporaryIndex = H[a];
    H[a] = H[b];
    H[b] = temporaryIndex;
}

//Function to maintain the heap property by moving down the heap
void heapify(HEAP *pHeap, ELEMENT **V, int index) {
    int smallestEntry = index;
    int left = 2 * index;
    int right = 2 * index + 1;

    if (left <= pHeap->size && V[pHeap->H[left]]->key < V[pHeap->H[smallestEntry]]->key) {
        smallestEntry = left;
    }
    if (right <= pHeap->size && V[pHeap->H[right]]->key < V[pHeap->H[smallestEntry]]->key) {
        smallestEntry = right;
    }

    if (smallestEntry != index) {
        swap(V, pHeap->H, index, smallestEntry);
        heapify(pHeap, V, smallestEntry);
    }
}

//Function to build the heap from the array
void buildHeap(HEAP *pHeap, ELEMENT **V, int n) {
    pHeap->size = n;
    for (int i = 1; i <= n; i++) {
        V[i]->pos = i;  //Sets position in the heap
        pHeap->H[i] = i; //Sets the heap array
    }
    for (int i = n / 2; i >= 1; i--) {
      heapify(pHeap, V, i); //Fills in the heap array 
    }
}

//Function to insert an element into the heap array
void insert(HEAP *pHeap, ELEMENT **V, int index) {
    if (pHeap->size >= pHeap->capacity) {
        fprintf(stderr, "Error: Heap capacity exceeded\n");
        return;
    }

    pHeap->size++;
    pHeap->H[pHeap->size] = index;
    V[index]->pos = pHeap->size;

    // Move the new element up to maintain the heap property
    int i = pHeap->size;
    while (i > 1 && V[pHeap->H[i / 2]]->key > V[pHeap->H[i]]->key) {
        swap(V, pHeap->H, i / 2, i);
        V[pHeap->H[i]]->pos = i;
        V[pHeap->H[i / 2]]->pos = i;
        i /= 2;
    }
}

// Function to extract the minimum element from the heap
ELEMENT* extractMin(HEAP *pHeap, ELEMENT **V) {
    if (pHeap->size == 0) {
        fprintf(stderr, "Error: Heap is empty\n");
        return NULL;
    }

    ELEMENT *minElement = V[pHeap->H[1]]; // The minimum element
    pHeap->H[1] = pHeap->H[pHeap->size]; // Move the last element to the root
    pHeap->size--;
    heapify(pHeap, V, 1); // Restore the heap property

    return minElement;
}

// Function to decrease the key of a given index in the heap
void decreaseKey(HEAP *pHeap, ELEMENT **V, int index, double key) {
    if (V[index]->key < key) {
        fprintf(stderr, "Error: New key is larger than current key\n");
        return;
    }

    V[index]->key = key; // Update the key
    int i = V[index]->pos; // Get the position of the updated element

    // Move the updated element up to restore the heap property
    while (i > 1 && V[pHeap->H[i / 2]]->key > V[pHeap->H[i]]->key) {
        swap(V, pHeap->H, i / 2, i);
        V[pHeap->H[i]]->pos = i;
        V[pHeap->H[i / 2]]->pos = i / 2;
        i /= 2;
    }
}

// Function to print the heap
void printHeap(HEAP *pHeap, ELEMENT **V) {
    printf("Heap elements:\n");
    for (int i = 1; i <= pHeap->size; i++) {
        printf("Index: %d, Key: %lf, Pos: %d\n", 
               V[pHeap->H[i]]->index, 
               V[pHeap->H[i]]->key, 
               V[pHeap->H[i]]->pos);
    }
}
