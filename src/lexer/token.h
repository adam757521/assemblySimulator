#pragma once

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
