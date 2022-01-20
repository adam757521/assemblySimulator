#ifndef ASMVM_LEXER_STREAM_H
#define ASMVM_LEXER_STREAM_H

typedef struct
{
    const char *buffer;
    int position;
} CharacterStream_t;

extern const char* numbers;
char CharacterStream_Next(CharacterStream_t *stream);
CharacterStream_t CharacterStream_Create(const char *buffer);
int CharacterStream_UntilNumEnd(CharacterStream_t* stream);
void CharacterStream_UntilStrEnd(CharacterStream_t* stream, char* buffer);
#endif
