#include <stdlib.h>
#include <stdio.h>
#include "../../../include/evaluator/memory/memory.h"

memory_t* Memory_Create(size_t size) {
    // TODO: Optimize usedMemory.
    memory_t* memory = malloc(sizeof(memory_t));
    memory->memory = malloc(sizeof(char) * size);
    memory->usedMemory = calloc(size, sizeof(size_t));
    memory->size = size;
    return memory;
}

void Memory_PrintMemoryTable(memory_t* memory) {
    for (int i = 0; i < memory->size; i++) {
        printf("%d ", memory->memory[i]);
    }
    printf("\n");
}

size_t Memory_FindFreeMemory(memory_t* memory, size_t size) {
    size_t memoryIndex = -1;
    size_t allocatedMemorySize = 0;

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

void* Memory_Malloc(memory_t* memory, size_t size) {
    if (size > memory->size) {
        return NULL;
    }

    size_t allocatedMemoryStartIndex = Memory_FindFreeMemory(memory, size);
    if (allocatedMemoryStartIndex == -1) {
        return NULL;
    }

    for (int i = 0; i < size; i++) {
        memory->usedMemory[allocatedMemoryStartIndex + i] = size;
    }

    return memory->memory + allocatedMemoryStartIndex;
}

void* Memory_Calloc(memory_t* memory, size_t size, char value) {
    char* ptr = Memory_Malloc(memory, size);
    if (ptr == NULL) {
        return NULL;
    }

    for (int i = 0; i < size; i++) {
        ptr[i] = value;
    }

    return ptr;
}

size_t Memory_GetMemorySize(memory_t* memory, void* ptr) {
    return memory->usedMemory[(int) ((char *) ptr - memory->memory)];
}

void Memory_Free(memory_t* memory, void* ptr) {
    int index = (int) ((char *) ptr - memory->memory);
    size_t memorySize = memory->usedMemory[index];

    for (int i = 0; i < memorySize; i++) {
        memory->usedMemory[index + i] = 0;
    }
}

void Memory_FreeAll(memory_t* memory) {
    free(memory->memory);
    free(memory->usedMemory);
    free(memory);
}
