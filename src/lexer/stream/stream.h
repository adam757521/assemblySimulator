#pragma once

typedef struct
{
    const char *buffer;
    int position;
} CharacterStream_t;

extern const char* numbers;
char CharacterStream_Next(CharacterStream_t *stream);
CharacterStream_t CharacterStream_Create(const char *buffer);
int CharacterStream_UntilNumEnd(CharacterStream_t* stream);
