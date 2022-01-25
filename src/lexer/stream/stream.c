#include <string.h>
#include <stdlib.h>
#include "../../../include/lexer/stream/stream.h"
#include "../../../include/lexer/utils/utils.h"
#include "../../../include/errors/errors.h"


const char* numbers = "0123456789";


/*
 * Returns a bool representing if the stream is done.
 * @param CharacterStream_t* stream - the stream to check.
 * @return int - 1 if the stream is done, 0 otherwise.
 */
int CharacterStream_Done(CharacterStream_t* stream) {
    return stream->position >= strlen(stream->buffer);
}

/*
 * Returns the next character from the stream.
 * If the stream is at the end of the file, the function returns -1.
 * @param CharacterStream_t* stream - the stream to read from.
 * @return char - the next character from the stream.
 */
char CharacterStream_Next(CharacterStream_t* stream) {
    if (!CharacterStream_Done(stream))
    {
        // Increments the position of the stream and returns the character at that position.
        stream->position++;
        return stream->buffer[stream->position - 1];
    }
    else
    {
        // Returns -1 if the stream is at the end of the file.
        return -1;
    }
}

/*
 * Returns the next full number from the stream.
 * @param CharacterStream_t* stream - the stream to read from.
 * @return uint64_t - the next full number from the stream.
 */
uint64_t CharacterStream_UntilNumEnd(CharacterStream_t* stream) {
    // Creates a buffer for the number.
    char buffer[1024];
    buffer[0] = '\0';

    while (!CharacterStream_Done(stream)) {
        char c = CharacterStream_Next(stream);

        if (strchr(numbers, c) == NULL) {
            // Break the loop if the character is not a number.
            break;
        }

        // Appends the character to the buffer.
        AppendChar(buffer, c);
    }

    // Converts the buffer to uint64_t.
    return atoll(buffer);
}

void CharacterStream_UntilStrEnd(CharacterStream_t* stream, char* buffer) {
    int done = 0;

    while (!CharacterStream_Done(stream)) {
        char c = CharacterStream_Next(stream);

        if (c == '"') {
            done = 1;
            break;
        }

        AppendChar(buffer, c);
    }

    Assert(done, "ERROR: String not closed");

    stream->position++;
}

CharacterStream_t CharacterStream_Create(const char* buffer) {
    CharacterStream_t stream;
    stream.buffer = buffer;
    stream.position = 0;
    return stream;
}
