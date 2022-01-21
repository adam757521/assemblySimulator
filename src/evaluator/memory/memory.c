#include <stdlib.h>
#include "memory.h"

memory_t* Memory_Create(int size) {
    memory_t* memory = malloc(sizeof(memory_t));
    memory->memory = malloc(sizeof(char) * size);
    memory->usedMemory = calloc(size, sizeof(int) * size);
    memory->size = size;
    return memory;
}

int Memory_FindFreeMemory(memory_t* memory, int size) {
    int memoryIndex = -1;
    int allocatedMemorySize = 0;

    for (int i = 0; i < memory->size; i++) {
        if (memory->usedMemory[i] != 0) {
            allocatedMemorySize = 0;
        } else {
            allocatedMemorySize++;
        }

        if (allocatedMemorySize == size) {
            memoryIndex = i - size + 1;
        }
    }

    return memoryIndex;
}

void* Memory_Malloc(memory_t* memory, int size) {
    if (size > memory->size) {
        return NULL;
    }

    int allocatedMemoryStartIndex = Memory_FindFreeMemory(memory, size);
    if (allocatedMemoryStartIndex == -1) {
        return NULL;
    }

    for (int i = 0; i < size; i++) {
        memory->usedMemory[allocatedMemoryStartIndex + i] = size;
    }

    return memory->memory + allocatedMemoryStartIndex;
}

void* Memory_Calloc(memory_t* memory, int size, char value) {
    char* ptr = Memory_Malloc(memory, size);
    if (ptr == NULL) {
        return NULL;
    }

    for (int i = 0; i < size; i++) {
        ptr[i] = value;
    }

    return ptr;
}

void Memory_Free(memory_t* memory, void* ptr) {
    int index = (int) ((char *) ptr - memory->memory);
    int memorySize = memory->usedMemory[index];

    for (int i = 0; i < memorySize; i++) {
        memory->usedMemory[index + i] = 0;
    }
}

void Memory_FreeAll(memory_t* memory) {
    free(memory->memory);
    free(memory->usedMemory);
    free(memory);
}
