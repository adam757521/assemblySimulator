#include <stdio.h>
#include <string.h>
#include "token.h"
#include "../list/list.h"

typedef CharacterStream_t CharacterStream_t, *pno;
typedef struct
{
    const char *buffer;
    int position;
    pno (*Next)(CharacterStream_t *);
} CharacterStream_t;

pno CharacterStream_Next(CharacterStream_t *stream)
{
    if (stream->position < strlen(stream->buffer))
    {
        stream->position++;
        return stream->buffer + stream->position - 1;
    }
    else
    {
        return NULL;
    }
}

CharacterStream_t CreateCharacterStream(const char *buffer)
{
    CharacterStream_t stream;
    stream.buffer = buffer;
    stream.position = 0;

    stream.Next = CharacterStream_Next;
    return stream;
}

Token *LexLine(const char *line)
{
    CharacterStream_t stream = CreateCharacterStream(line);
    list_t resultTokens = CreateDynamicList();

    while (stream.Next(&stream) != NULL)
    {
        token = Token_Create(stream.Next(&stream));
        if (token == NULL)
        {
            break;
        }
        printf("%s\n", token->value);
    }
    return token;
}
