#include <stdio.h>
#include <string.h>
#include "../../include/evaluator/program/program.h"
#include "../../include/lexer/function/function.h"
#include "../../include/errors/errors.h"
#include "../../include/evaluator/instructions/instructions.h"

function_t* FindMainFunction(program_t *program) {
    for (int i = 0; i < program->functions->used; i++) {
        function_t *function = program->functions->items[i];

        if (strcmp(function->definitionToken->string, "main") == 0) {
            return function;
        }
    }

    return NULL;
}

void RunFunction(function_t *function, program_t *program) {
    printf("Running function %s\n", function->definitionToken->string);

    for (int i = 0; i < function->body->used; i++) {
        instruction_t* instruction = function->body->items[i];

        Instruction_Call(instruction, program);
    }
}

void RunProgram(program_t* program) {
    function_t *mainFunction = FindMainFunction(program);

    if (mainFunction == NULL) {
        ErrorExit("ERROR: No main function found.");
    }

    RunFunction(mainFunction, program);
}