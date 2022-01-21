#include <stdlib.h>
#include "../../../include/list/list.h"
#include "../../../include/lexer/function/function.h"

list_t* OrganizeTokens(list_t* tokens) {
    // list_t* (function_t*)
    list_t* organizedFunctions = CreateDynamicList();
    function_t* currentFunction = NULL;

    for (int i = 0; i < tokens->used; i++) {
        token_t* currentToken = tokens->items[i];

        if (currentToken->type == Function) {
            if (currentFunction != NULL) {
                ListAppend(organizedFunctions, currentFunction);
            }

            // list_t* (Token*)
            list_t* functionBody = CreateDynamicList();
            currentFunction = Function_Create(currentToken, functionBody);
        } else if (currentFunction != NULL) {
            ListAppend(currentFunction->body, currentToken);
        } else {
            // Destroy the token, since it is not in a function.
            DestroyToken(currentToken);
        }
    }

    if (currentFunction != NULL) {
        ListAppend(organizedFunctions, currentFunction);
    }

    return organizedFunctions;
}