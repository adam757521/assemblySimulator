#pragma once

enum TokenType
{
    Number,
    String,
    Pointer
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
