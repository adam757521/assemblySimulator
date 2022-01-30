#include <string.h>
#include "../../../include/evaluator/program/program.h"
#include "../../../include/lexer/function/function.h"
#include "../../../include/errors/errors.h"

const char* registers[] = {"eax", "ebx", "ecx", "edx", "esi", "edi", "ebp", "esp", "cf"};

inline void* Program_GetMemory(program_t* program, token_t* token) {
    void* memory = Program_GetMemoryByToken(program, token);
    return memory ? memory : &token->pointer;
}

program_t* Program_Create(size_t memorySize, list_t* functions) {
    program_t* program = malloc(sizeof(program_t));

    program->functions = functions;
    program->memory = Memory_Create(memorySize);
    program->registers = CreateDynamicList();
    program->variables = CreateDynamicList();
    program->variablePointers = CreateDynamicList();

    for (int i = 0; i < 8; i++) {
        void* reg = Memory_Malloc(program->memory, 8);
        if (reg == NULL) {
            return NULL;
        }

        ListAppend(program->registers, reg);
    }

    void* cf = Memory_Malloc(program->memory, 1);
    if (cf == NULL) {
        return NULL;
    }

    ListAppend(program->registers, cf);

    return program;
}

void* Program_GetRegister(program_t* program, token_t* token) {
    if (token->type != Word) {
        return NULL;
    }

    for (int i = 0; i < program->registers->used; i++) {
        char* tokenString = token->string;
        const char* registerString = registers[i];

        if (strcmp(tokenString, registerString) == 0) {
            return program->registers->items[i];
        }
    }

    return NULL;
}

void Program_Free(program_t* program) {
    for (int i = 0; i < program->functions->used; i++) {
        Function_Free(program->functions->items[i]);
    }

    Memory_FreeAll(program->memory);
    ListFree(program->registers, 0);
    ListFree(program->variables, 0); // Will be freed with tokens.
    ListFree(program->variablePointers, 0);
    free(program);
}

void* Program_GetVariable(program_t* program, token_t* token) {
    if (token->type != Word) {
        return NULL;
    }

    for (int i = 0; i < program->variables->used; i++) {
        if (strcmp(token->string, program->variables->items[i]) == 0) {
            return program->variablePointers->items[i];
        }
    }

    return NULL;
}

void* Program_GetMemoryByToken(program_t* program, token_t* token) {
    void* ptr = Program_GetRegister(program, token);
    if (ptr != NULL) {
        return ptr;
    }

    ptr = Program_GetVariable(program, token);
    if (ptr != NULL) {
        return ptr;
    }

    return NULL;
}

int64_t Program_GetMemoryValue(program_t* program, void* ptr) {
    if (ptr == NULL) {
        return 0;
    }

    int64_t value;
    memcpy(&value, ptr, Memory_GetMemorySize(program->memory, ptr));
    return value;
}

void Program_SetMemoryValue(program_t* program, void* ptr, int64_t value) {
    if (ptr == NULL) {
        return;
    }

    memcpy(ptr, &value, Memory_GetMemorySize(program->memory, ptr));
}

void Program_AddVariable(program_t* program, char* name, int size) {
    void* pointer = Memory_Malloc(program->memory, size);
    Assert(pointer != NULL, "ERROR: Could not allocate memory for %s.\n", name);

    ListAppend(program->variables, name);
    ListAppend(program->variablePointers, pointer);
}