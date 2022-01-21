#include <stdio.h>
#include "lexer/lexer.h"
#include "errors/errors.h"
#include "lexer/organizer/organizer.h"
#include "lexer/function/function.h"
#include "evaluator/program/program.h"
#include "evaluator/evaluator.h"
#include "evaluator/memory/memory.h"

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        // TODO: change this to proper file.
        argv[1] = "../test.asm";
        //ErrorExit("Usage: %s <file>", argv[0]);
    }

    FILE* file = fopen(argv[1], "r");
    if (file == NULL) {
        ErrorExit("Could not open file %s", argv[1]);
    }

    list_t* tokens = LexFile(file);
    fclose(file);

    list_t* functions = OrganizeTokens(tokens);
    ListFree(tokens, 0);

    program_t program;
    program.functions = functions;
    program.memory = Memory_Create(256);

    RunProgram(&program);

    Program_Free(&program);

    return 0;
}