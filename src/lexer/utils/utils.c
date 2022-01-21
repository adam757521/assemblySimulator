#include <string.h>
#include "../../../include/list/list.h"
#include "../../../include/lexer/token/token.h"

void AppendChar(char *str, char c) {
    int len = strlen(str);
    str[len] = c;
    str[len + 1] = '\0';
}

void FreeTokenList(list_t* tokens) {
    for (int i = 0; i < tokens->used; i++) {
        DestroyToken(tokens->items[i]);
    }

    ListFree(tokens, 0);
}
