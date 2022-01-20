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
        int number;
        char *string;
        void *pointer;
    };
} Token;

void VisualizeToken(Token* token);
void DestroyToken(Token* token);
#endif
