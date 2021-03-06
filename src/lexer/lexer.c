#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../../include/lexer/lexer.h"
#include "../../include/lexer/token/token.h"
#include "../../include/lexer/stream/stream.h"
#include "../../include/lexer/utils/utils.h"

void SetToken(list_t* resultTokens, token_t **token, enum TokenType type, char* word) {
    (*token)->type = type;

    word[0] = '\0';
    ListAppend(resultTokens, *token);
    *token = malloc(sizeof(token_t));
}

char* CreateCharArrayCpy(char* word) {
    char* wordCpy = malloc(sizeof(char) * (strlen(word) + 1));
    strcpy(wordCpy, word);
    return wordCpy;
}

list_t* LexLine(const char *line, int lineNum)
{
    CharacterStream_t stream = CharacterStream_Create(line);
    list_t* resultTokens = CreateDynamicList();

    char currentWord[1024] = "";

    // TODO: dynamically allocate the token line?
    token_t* currentToken = malloc(sizeof(token_t));
    currentToken->line = lineNum;

    char nextCharacter = CharacterStream_Next(&stream);
    while (nextCharacter != -1)
    {
        currentToken->column = stream.position;

        if (nextCharacter == '\n') {
            break;
        }

        if (strchr(numbers, nextCharacter) != NULL) {
            stream.position--;

            currentToken->number = CharacterStream_UntilNumEnd(&stream);

            if (currentWord[0] == '-') {
                currentToken->number = -currentToken->number;
            }

            SetToken(resultTokens, &currentToken, Number, currentWord);

            nextCharacter = CharacterStream_Next(&stream);
            continue;
        }

        char* wordCopy = CreateCharArrayCpy(currentWord);
        currentToken->string = wordCopy;

        if (nextCharacter == '"') {
            // TODO: Rework this logic.
            free(wordCopy);
            CharacterStream_UntilStrEnd(&stream, currentWord);

            wordCopy = CreateCharArrayCpy(currentWord);
            currentToken->string = wordCopy;

            SetToken(resultTokens, &currentToken, String, currentWord);
        } else if (nextCharacter == ' ' && strlen(currentWord) > 0) {
            SetToken(resultTokens, &currentToken, Word, currentWord);
        } else if (nextCharacter == ':') {
            SetToken(resultTokens, &currentToken, Function, currentWord);
        } else {
            free(wordCopy);

            if (nextCharacter != 32) {
                AppendChar(currentWord, nextCharacter);
            }
        }

        nextCharacter = CharacterStream_Next(&stream);
    }

    char* wordCopy = CreateCharArrayCpy(currentWord);
    if (strlen(wordCopy) > 0) {
        currentToken->string = wordCopy;
        SetToken(resultTokens, &currentToken, Word, currentWord);
    }

    return resultTokens;
}

list_t* LexFile(FILE* file)
{
    list_t* resultTokens = CreateDynamicList();

    char line[1024];
    int lineNum = 0;
    while (fgets(line, 1024, file) != NULL) {
        lineNum++;
        list_t* tokens = LexLine(line, lineNum);

        for (int i = 0; i < tokens->used; i++) {
            ListAppend(resultTokens, tokens->items[i]);
        }

        ListFree(tokens, 0);
    }

    return resultTokens;
}
