#include <stdint.h>

#ifndef ASMVM_LEXER_TOKEN_TOKEN_H
#define ASMVM_LEXER_TOKEN_TOKEN_H

enum TokenType
{
    Word,
    Number,
    String,
    Pointer,
    Function
};

typedef struct
{
    enum TokenType type;
    int line;
    int column;
    union
    {
        uint64_t number;
        char *string;
        void *pointer;
    };
} token_t;

void VisualizeToken(token_t* token);
void DestroyToken(token_t* token);
#endif
