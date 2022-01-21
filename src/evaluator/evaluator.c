#include <stdio.h>
#include <string.h>
#include "program/program.h"
#include "function/function.h"
#include "../errors/errors.h"

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
}

void RunProgram(program_t* program) {
    function_t *mainFunction = FindMainFunction(program);

    if (mainFunction == NULL) {
        ErrorExit("ERROR: No main function found.");
    }

    RunFunction(mainFunction, program);
}