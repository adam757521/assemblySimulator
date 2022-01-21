#include <stdlib.h>
#include "../../../include/lexer/function/function.h"
#include "../../../include/lexer/utils/utils.h"

void Function_Free(function_t* function) {
    DestroyToken(function->definitionToken);
    FreeTokenList(function->body);

    // Assumes the function is dynamically allocated.
    free(function);
}

function_t* Function_Create(token_t* definitionToken, list_t* body) {
    function_t* function = (function_t*)malloc(sizeof(function_t));
    function->definitionToken = definitionToken;
    function->body = body;

    return function;
}