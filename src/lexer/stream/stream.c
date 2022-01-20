#include <string.h>
#include <stdlib.h>
#include "stream.h"
#include "../utils.h"


const char* numbers = "0123456789";


char CharacterStream_Next(CharacterStream_t* stream) {
    if (stream->position < strlen(stream->buffer))
    {
        stream->position++;
        return stream->buffer[stream->position - 1];
    }
    else
    {
        return -1;
    }
}

int CharacterStream_Done(CharacterStream_t* stream) {
    return stream->position >= strlen(stream->buffer);
}

int CharacterStream_UntilNumEnd(CharacterStream_t* stream) {
    char buffer[1024];
    buffer[0] = '0';  //TODO: find better way of doing this?

    while (!CharacterStream_Done(stream)) {
        char c = CharacterStream_Next(stream);

        if (strchr(numbers, c) == NULL) {
            break;
        }

        AppendChar(buffer, c);
    }

    return atoi(buffer);
}

const char* CharacterStream_UntilStringEnd(CharacterStream_t* stream, char* buffer) {
    while (!CharacterStream_Done(stream)) {
        char c = CharacterStream_Next(stream);

        if (c == '"') {
            break;
        }

        AppendChar(buffer, c);
    }

    stream->position--;
    return buffer;
}

CharacterStream_t CharacterStream_Create(const char* buffer) {
    CharacterStream_t stream;
    stream.buffer = buffer;
    stream.position = 0;
    return stream;
}
