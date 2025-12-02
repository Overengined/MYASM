#include <stdlib.h> 
#include "MYASM.h"
#include <stdio.h>

struct memger {
    long long int* memory;
    long long int size;
};

struct memger* newmem(long long int size) {
    // initialise a memger struct, memory points to an array to hold 'size' integers
    struct memger* m = (struct memger*) malloc(sizeof(struct memger));
    m->memory = (long long int*) malloc(size * sizeof(int));
    m->size = size;
    return m;
}

int getmem(struct memger* m, long long int index) {
    // get the integer at memory[index]
    if (index < 0 || index >= m->size) {
        // out of bounds
        if (verbose) {
            printf("MEMGER RECOMMENDS TERM: getmem index %lld out of bounds (size %lld)\n", index, m->size);
        }
        return 1;
    }
    return m->memory[index];
}

int setmem(struct memger* m, long long int index, int value) {
    // set the integer at memory[index] to value
    if (index < 0 || index >= m->size) {
        // out of bounds
        if (verbose) {
            printf("MEMGER RECOMMENDS TERM: setmem index %lld out of bounds (size %lld)\n", index, m->size);
        }
        return 1;
    }
    m->memory[index] = value;
    return 0;
}