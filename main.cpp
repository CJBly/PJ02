#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "heap.h"
#include "data_structures.h"

int main(int argc, char **argv) {
    FILE *fp1, *fp2;
    HEAP *pHeap;
    ELEMENT **V;
    double key;
    int returnV, n;
    char word[100];

    // Check command line arguments
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <I-File> <O-File>\n", argv[0]);
        exit(0);
    }

    // Open output file
    fp2 = fopen(argv[2], "w");
    if (!fp2) {
        fprintf(stderr, "Error: cannot open file %s\n", argv[2]);
        exit(0);
    }

    // Initialize V and pHeap
    V = NULL;
    pHeap = NULL;

    // Loop over the instructions
    while (1) {
        returnV = nextInstruction(word, &n, &key);

        if (returnV == 0) {
            fprintf(stderr, "Warning: Invalid instruction: %s\n", word);
            continue;
        }

        if (strcmp(word, "Stop") == 0) {
            if (fp2) fclose(fp2);
            return 0;
        }

        if (strcmp(word, "Read") == 0) {
            fp1 = fopen(argv[1], "r");
            if (!fp1) {
                fprintf(stderr, "Error: cannot open file %s\n", argv[1]);
                exit(0);
            }
            fscanf(fp1, "%d", &n);
            V = (ELEMENT **)malloc((n + 1) * sizeof(ELEMENT *));
            for (int i = 1; i <= n; i++) {
                V[i] = (ELEMENT *)malloc(sizeof(ELEMENT));
                fscanf(fp1, "%lf", &V[i]->key);
                V[i]->index = i;
                V[i]->pos = 0;
            }
            fclose(fp1);

            // Allocate memory for heap
            pHeap = (HEAP *)malloc(sizeof(HEAP));
            pHeap->capacity = n;
            pHeap->size = 0;
            pHeap->H = (int *)malloc((n + 1) * sizeof(int));
            continue;
        }

        if (strcmp(word, "PrintArray") == 0) {
            if (!V) {
                fprintf(stderr, "Error: array is NULL\n");
                continue;
            }
            for (int i = 1; i <= n; i++) {
                printf("Index: %d, Key: %lf, Pos: %d\n", V[i]->index, V[i]->key, V[i]->pos);
            }
            continue;
        }

        if (strcmp(word, "BuildHeap") == 0) {
            if (!pHeap) {
                fprintf(stderr, "Error: heap is NULL\n");
                continue;
            }
            buildHeap(pHeap, V, n);
            continue;
        }

        if (strcmp(word, "Insert") == 0) {
            if (n < 1) {
                fprintf(stderr, "Error: index out of bounds\n");
                continue;
            }
            insert(pHeap, V, n);
            continue;
        }

        if (strcmp(word, "ExtractMin") == 0) {
            if (!pHeap || pHeap->size == 0) {
                fprintf(stderr, "Error: heap is NULL or empty\n");
                continue;
            }
            ELEMENT* minElement = extractMin(pHeap, V);
            if (minElement) {
                printf("Element with index %d and key %lf extracted from the heap\n", minElement->index, minElement->key);
            }
            continue;
        }

        if (strcmp(word, "DecreaseKey") == 0) {
            decreaseKey(pHeap, V, n, key);
            continue;
        }

        if (strcmp(word, "PrintHeap") == 0) {
            if (!pHeap) {
                fprintf(stderr, "Error: heap is NULL\n");
                continue;
            }
            printHeap(pHeap, V);
            continue;
        }

        fprintf(stderr, "Warning: Unknown instruction: %s\n", word);
    }

    return 0;
}
