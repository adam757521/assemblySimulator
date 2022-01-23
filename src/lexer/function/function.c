#include <stdlib.h>
#include "../../../include/lexer/function/function.h"
#include "../../../include/lexer/utils/utils.h"
#include "../../../include/evaluator/instructions/instructions.h"

void Function_Free(function_t* function) {
    DestroyToken(function->definitionToken);

    for (int i = 0; i < function->body->used; i++) {
        Instruction_Free(function->body->items[i]);
    }

    // Assumes the function is dynamically allocated.
    free(function);
}

function_t* Function_Create(token_t* definitionToken, list_t* body) {
    function_t* function = (function_t*)malloc(sizeof(function_t));
    function->definitionToken = definitionToken;
    function->body = body;

    return function;
}