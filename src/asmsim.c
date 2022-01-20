#include <stdio.h>
#include "lexer/token.h"
#include "lexer/lexer.h"
#include "errors/errors.h"

int main()
{
    ErrorExit("ERROR: %s.\n", "This program is still under work");

    list_t tokens = LexLine("mov 1312", 1);
    for (int i = 0; i < tokens.used; i++) {
        Token* token = (Token*)tokens.items[i];
        printf("%d, %d\n", token->type, token->number);
    }

    ListFree(&tokens, 1);

    return 0;
}