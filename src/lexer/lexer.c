#include <stdlib.h>
#include <string.h>
#include "lexer.h"
#include "token.h"
#include "stream/stream.h"
#include "utils.h"

list_t LexLine(const char *line, int lineNum)
{
    CharacterStream_t stream = CharacterStream_Create(line);
    list_t resultTokens = CreateDynamicList();

    char currentWord[1024];

    Token* currentToken = malloc(sizeof(Token));
    currentToken->line = lineNum;

    char nextCharacter = CharacterStream_Next(&stream);
    while (nextCharacter != -1)
    {
        currentToken->column = stream.position;

        AppendChar(currentWord, nextCharacter);

        if (nextCharacter == ' ') {
            if (strlen(currentWord) > 0) {
                currentToken->type = Word;
                currentToken->string = currentWord;

                currentWord[0] = '\0';
                ListAppend(&resultTokens, currentToken);
                currentToken = malloc(sizeof(Token));
            }
        }

        if (nextCharacter == ':') {
            currentToken->type = Function;
            currentToken->string = currentWord;

            currentWord[0] = '\0';
            ListAppend(&resultTokens, currentToken);
            currentToken = malloc(sizeof(Token));
        }

        if (strchr(numbers, nextCharacter) != NULL) {
            stream.position--;

            currentToken->type = Number;
            currentToken->number = CharacterStream_UntilNumEnd(&stream);

            ListAppend(&resultTokens, currentToken);
            currentToken = malloc(sizeof(Token));  //TODO: optimize this code section
        }

        nextCharacter = CharacterStream_Next(&stream);
    }

    return resultTokens;
}
