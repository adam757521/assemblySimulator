#include <stdio.h>
#include "../include/lexer/lexer.h"
#include "../include/errors/errors.h"
#include "../include/lexer/organizer/organizer.h"
#include "../include/lexer/function/function.h"
#include "../include/evaluator/program/program.h"
#include "../include/evaluator/evaluator.h"

int main(int argc, char** argv)
{
    argv[1] = "../test2.asm";

    if (argc < 2)
    {
        //ErrorExit("Usage: %s <file>", argv[0]);
    }

    FILE* file = fopen(argv[1], "r");
    if (file == NULL) {
        ErrorExit("Could not open file %s", argv[1]);
    }

    list_t* tokens = LexFile(file);
    fclose(file);

    program_t* program = Program_Create(256, OrganizeTokens(tokens));
    ListFree(tokens, 0);

    RunProgram(program);
    Program_Free(program);

    return 0;
}