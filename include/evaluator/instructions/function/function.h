#ifndef ASMVM_INSTRUCTION_FUNCTION_H
#define ASMVM_INSTRUCTION_FUNCTION_H

#include "../../program/program.h"
#include "../instructions.h"

typedef void(*instruction_f)(void**, program_t*);

typedef struct {
    int arguments_count;
    instruction_f function;
} instruction_function_t;

#endif //ASMVM_INSTRUCTION_FUNCTION_H
