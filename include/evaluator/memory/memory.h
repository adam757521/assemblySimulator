#ifndef ASMVM_MEMORY_H
#define ASMVM_MEMORY_H

typedef struct {
    char* memory;
    size_t* usedMemory;
    size_t size;
} memory_t;

memory_t* Memory_Create(size_t size);
void Memory_PrintMemoryTable(memory_t* memory);
size_t Memory_FindFreeMemory(memory_t* memory, size_t size);
void* Memory_Malloc(memory_t* memory, size_t size);
void* Memory_Calloc(memory_t* memory, size_t size, char value);
void Memory_Free(memory_t* memory, void* ptr);
void Memory_FreeAll(memory_t* memory);
size_t Memory_GetMemorySize(memory_t* memory, void* ptr);

#endif //ASMVM_MEMORY_H
