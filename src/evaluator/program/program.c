#include "../../../include/evaluator/program/program.h"
#include "../../../include/lexer/function/function.h"

void Program_Free(program_t* program) {
    for (int i = 0; i < program->functions->used; i++) {
        Function_Free(program->functions->items[i]);
    }

    Memory_FreeAll(program->memory);
}