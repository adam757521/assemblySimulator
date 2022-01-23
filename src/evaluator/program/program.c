#include <string.h>
#include "../../../include/evaluator/program/program.h"
#include "../../../include/lexer/function/function.h"

const char* registers[] = {"eax", "ebx", "ecx", "edx", "esi", "edi", "ebp", "esp"};

program_t* Program_Create(int memorySize, list_t* functions) {
    program_t* program = malloc(sizeof(program_t));

    program->functions = functions;
    program->memory = Memory_Create(memorySize);
    program->registers = CreateDynamicList();

    for (int i = 0; i < 8; i++) {
        void* reg = Memory_Malloc(program->memory, 8);
        if (reg == NULL) {
            return NULL;
        }

        ListAppend(program->registers, reg);
    }

    return program;
}

void* Program_GetRegister(program_t* program, token_t* token) {
    if (token->type != Word) {
        return NULL;
    }

    for (int i = 0; i < program->registers->used; i++) {
        if (strcmp(token->string, registers[i]) == 0) {
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
    free(program);
}