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
} program_t;

program_t* Program_Create(int memorySize, list_t* functions);
void Program_Free(program_t* program);
void* Program_GetRegister(program_t* program, token_t* token);

#endif //ASMVM_PROGRAM_H
