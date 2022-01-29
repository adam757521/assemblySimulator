#include "../../list/list.h"
#include "../memory/memory.h"
#include "../../lexer/token/token.h"

#ifndef ASMVM_PROGRAM_H
#define ASMVM_PROGRAM_H

extern const char* registers[];

typedef struct {
    list_t* functions;
    memory_t* memory;
    list_t* registers;
    list_t* variables;
    list_t* variablePointers;
} program_t;

program_t* Program_Create(int memorySize, list_t* functions);
void Program_Free(program_t* program);
void* Program_GetRegister(program_t* program, token_t* token);
void Program_AddVariable(program_t* program, char* name, int size);
int64_t Program_GetMemoryValue(program_t* program, void* ptr);
void Program_SetMemoryValue(program_t* program, void* ptr, int64_t value);
void* Program_GetMemoryByToken(program_t* program, token_t* token);
#endif //ASMVM_PROGRAM_H
