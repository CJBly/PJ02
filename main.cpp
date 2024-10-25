#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"
#include "heap.h"
#include "data_structures.h"

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: ./PJ2 <I-File> <O-File>\n<I-File> is the input file\n<O-File> is the output file\n");
        return 1;
    }

    FILE *inputFile, *outputFile;
    HEAP *pHeap = NULL;
    ELEMENT **V = NULL;
    int n = 0;
    char instruction[100];
    int index;
    double newKey;

    while (1) {
        nextInstruction(instruction, &index, &newKey);

        if (strcmp(instruction, "Stop") == 0) {
            fprintf(stdout, "Instruction: Stop\n");
            break;
        } else if (strcmp(instruction, "Read") == 0) {
            fprintf(stdout, "Instruction: Read\n");
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
        } else if (strcmp(instruction, "PrintArray") == 0) {
            printArray(V, n);
        } else if (strcmp(instruction, "PrintHeap") == 0) {
            printHeap(pHeap, V);
        } else if (strcmp(instruction, "BuildHeap") == 0) {
            fprintf(stdout, "Instruction: BuildHeap\n");
            buildHeap(pHeap, V, n);
        } else if (strcmp(instruction, "Insert") == 0) {
            fprintf(stdout, "Instruction: Insert %d\n", index);
            if (index < 1 || index > n) {
                fprintf(stderr, "Error: index out of bound\n");
            } else if (V[index]->pos != 0) {
                fprintf(stderr, "Error: V[%d] already in the heap\n", index);
            } else {
                insert(pHeap, V, index);
                fprintf(stdout, "Element V[%d] inserted into the heap\n", index);
            }
        } else if (strcmp(instruction, "ExtractMin") == 0) {
            fprintf(stdout, "Instruction: ExtractMin\n");
            if (!pHeap) {
                fprintf(stderr, "Error: heap is NULL\n");
            } else if (pHeap->size == 0) {
                fprintf(stderr, "Error: heap is empty\n");
            } else {
                ELEMENT *minElement = extractMin(pHeap, V);
                if (minElement) {
                    fprintf(stdout, "Element with index %d and key %lf extracted from the heap\n", minElement->index, minElement->key);
                }
            }
        } else if (strcmp(instruction, "DecreaseKey") == 0) {
            fprintf(stdout, "Instruction: DecreaseKey %d %lf\n", index, newKey);
            if (index < 1 || index > n || newKey >= V[index]->key) {
                fprintf(stderr, "Error: invalid call to DecreaseKey\n");
            } else if (V[index]->pos == 0) {
                fprintf(stderr, "Error: V[%d] not in the heap\n", index);
            } else {
                decreaseKey(pHeap, V, index, newKey);
            }
        } else if (strcmp(instruction, "Write") == 0) {
            fprintf(stdout, "Instruction: Write\n");
            outputFile = fopen(argv[2], "w");
            if (!outputFile) {
                fprintf(stderr, "Error: cannot open file %s\n", argv[2]);
                continue;
            }
            for (int i = 1; i <= n; i++) {
                fprintf(outputFile, "%d %lf %d\n", V[i]->index, V[i]->key, V[i]->pos);
            }
            fclose(outputFile);
        } else {
            fprintf(stdout, "Warning: Invalid instruction\n");
        }
    }

    // Free memory and clean up
    for (int i = 1; i <= n; i++) {
        free(V[i]);
    }
    free(V);
    free(pHeap->H);
    free(pHeap);

    return 0;
}
