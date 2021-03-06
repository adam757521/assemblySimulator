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
 * @return int64_t - the next full number from the stream.
 */
int64_t CharacterStream_UntilNumEnd(CharacterStream_t* stream) {
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

    // Converts the buffer to int64_t.
    return atoll(buffer);
}

/*
 * Returns the next full string from the stream.
 * @param CharacterStream_t* stream - the stream to read from.
 * @param char* buffer - the buffer to store the string in.
 * @return void.
 */
void CharacterStream_UntilStrEnd(CharacterStream_t* stream, char* buffer) {
    // Creates a boolean representing if the string is closed.
    int done = 0;

    while (!CharacterStream_Done(stream)) {
        // Gets the next character from the stream.
        char c = CharacterStream_Next(stream);

        // Checks if the character is a quote, if it is, break and set done to 1 (true).
        if (c == '"') {
            done = 1;
            break;
        }

        if (c == '\\') {
            // Gets the next character from the stream.
            c = CharacterStream_Next(stream);

            if (c == 'n') {
                c = '\n';
            }
        }

        // Append the character to the buffer if it is not \0.
        if (c != '\0') {
            AppendChar(buffer, c);
        }
    }

    // If the string is not closed, throw an error.
    Assert(done, "ERROR: String not closed");

    stream->position++;
}

/*
 * Creates a new CharacterStream_t.
 * @param const char* buffer - the buffer to read from.
 * @return CharacterStream_t* - the new CharacterStream_t.
 */
CharacterStream_t CharacterStream_Create(const char* buffer) {
    CharacterStream_t stream;
    stream.buffer = buffer;
    stream.position = 0;
    return stream;
}
