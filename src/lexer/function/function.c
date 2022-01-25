#include <stdlib.h>
#include "../../../include/lexer/function/function.h"
#include "../../../include/lexer/utils/utils.h"
#include "../../../include/evaluator/instructions/instructions.h"

/*
 * Frees the memory allocated for the function.
 * @param function_t* function - the function to be freed.
 * @return - void.
 */
void Function_Free(function_t* function) {
    DestroyToken(function->definitionToken);

    for (int i = 0; i < function->body->used; i++) {
        Instruction_Free(function->body->items[i]);
    }

    // Assumes the function is dynamically allocated.
    free(function);
}

/*
 * Creates a new function.
 * @param token_t* definitionToken - the token that defines the function.
 * @param list_t* body - the body of the function.
 * @return - the new function (function_t*).
 */
function_t* Function_Create(token_t* definitionToken, list_t* body) {
    // Allocates the memory for the function.
    function_t* function = (function_t*)malloc(sizeof(function_t));

    // Initializes the function.
    function->definitionToken = definitionToken;
    function->body = body;

    return function;
}