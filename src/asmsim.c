#include <stdio.h>
#include "token/token.h"
#include "lexer/lexer.h"
#include "errors/errors.h"

void FreeTokens(list_t* tokens) {
    // Tokens = list_t* (list_t*) -> list_t* (Token**)

    for (int i = 0; i < tokens->used; i++) {
        // Get list_t* (Token**)
        list_t* tokenGroup = (list_t*)tokens->items[i];

        // Free Token**
        for (int j = 0; j < tokenGroup->used; j++) {
            // Free Token*
            DestroyToken(tokenGroup->items[j]);
        }

        // Free list_t* (Token**)
        ListFree(tokens->items[i], 0);
    }

    // Free list_t* (list_t*) -> list_t* (Token**)
    ListFree(tokens, 0);
}

int main(int argc, char** argv)
{
    if (argc != 2)
    {
        argv[1] = "../test.asm";
        //ErrorExit("Usage: %s <file>", argv[0]);
    }

    FILE* file = fopen(argv[1], "r");
    if (file == NULL) {
        ErrorExit("Could not open file %s", argv[1]);
    }

    list_t* tokens = LexFile(file);
    fclose(file);

    for (int i = 0; i < tokens->used; i++)
    {
        list_t* token = (list_t*)tokens->items[i];

        for (int j = 0; j < token->used; j++)
        {
            Token* t = (Token*)token->items[j];
            VisualizeToken(t);
        }
    }

    FreeTokens(tokens);

    return 0;
}