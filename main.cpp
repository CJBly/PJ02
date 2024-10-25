#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "heap.h"
#include "data_structures.h"

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <I-File> <O-File>\n", argv[0]);
        return 1;
    }

    FILE *inputFile, *outputFile;
    HEAP *pHeap = NULL;
    ELEMENT **V = NULL;
    int n;
    char instruction[100];
    double key;

    outputFile = fopen(argv[2], "w");
    if (!outputFile) {
        fprintf(stderr, "Error: cannot open file %s\n", argv[2]);
        return 1;
    }

    while (1) {
        int res = nextInstruction(instruction, &n, &key);
        
        if (strcmp(instruction, "Stop") == 0) {
            fprintf(stdout, "Instruction: Stop\n");
            break;
        } else if (strcmp(instruction, "Read") == 0) {
            inputFile = fopen(argv[1], "r");
            if (!inputFile) {
                fprintf(stderr, "Error: cannot open file %s\n", argv[1]);
                continue;
            }
            fscanf(inputFile, "%d", &n);
            V = (ELEMENT **)malloc((n + 1) * sizeof(ELEMENT *));
            for (int i = 1; i <= n; i++) {
                V[i] = (ELEMENT *)malloc(sizeof(ELEMENT));
                fscanf(inputFile, "%lf", &V[i]->key);
                V[i]->index = i;
                V[i]->pos = 0;
            }
            fclose(inputFile);

            pHeap = (HEAP *)malloc(sizeof(HEAP));
            pHeap->capacity = n;
            pHeap->size = 0;
            pHeap->H = (int *)malloc((n + 1) * sizeof(int));
        }
        else if (strcmp(instruction, "BuildHeap") == 0) {
            buildHeap(pHeap, V, n);
        }
        else if (strcmp(instruction, "Insert") == 0) {
            insert(pHeap, V, n);
        }
        else if (strcmp(instruction, "ExtractMin") == 0) {
            ELEMENT *minElement = extractMin(pHeap, V);
            if (minElement) {
                printf("Element with index %d and key %lf extracted\n", minElement->index, minElement->key);
            }
        }
    }
    fclose(outputFile);
    return 0;
}
