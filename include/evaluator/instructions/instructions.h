#ifndef ASMVM_INSTRUCTIONS_H
#define ASMVM_INSTRUCTIONS_H

#include "../../lexer/token/token.h"
#include "../../list/list.h"
#include "../program/program.h"

typedef struct {
    const char* type;
    list_t* arguments; // list_t* -> token_t*
} instruction_t;

instruction_t* Instruction_Create(const char* type);
int IsStringInstruction(const char* string);
void Instruction_Free(instruction_t* instruction);
void Instruction_Call(instruction_t* instruction, program_t* program);

#endif //ASMVM_INSTRUCTIONS_H
