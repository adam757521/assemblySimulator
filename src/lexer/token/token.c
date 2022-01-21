#include <stdio.h>
#include <stdlib.h>
#include "token.h"

void VisualizeToken(token_t* token) {
    printf("Token of type %d at line %d, column %d. Value: ", token->type, token->line, token->column);

    switch (token->type) {
        case Function:
        case String:
        case Word:
            printf("%s\n", token->string);
            break;
        case Number:
            printf("%d\n", token->number);
            break;
        case Pointer:
            printf("%p\n", token->pointer);
    }
}

void DestroyToken(token_t* token) {
    if (token->type == Function || token->type == String || token->type == Word) {
        free(token->string);
    }

    free(token);
}
