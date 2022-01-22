#ifndef ASMVM_MEMORY_H
#define ASMVM_MEMORY_H

typedef struct {
    char* memory;
    int* usedMemory;
    int size;
} memory_t;

memory_t* Memory_Create(int size);
void Memory_PrintMemoryTable(memory_t* memory);
int Memory_FindFreeMemory(memory_t* memory, int size);
void* Memory_Malloc(memory_t* memory, int size);
void* Memory_Calloc(memory_t* memory, int size, char value);
void Memory_Free(memory_t* memory, void* ptr);
void Memory_FreeAll(memory_t* memory);

#endif //ASMVM_MEMORY_H
