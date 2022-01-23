#include <stdlib.h>
#include "../../../include/list/list.h"
#include "../../../include/lexer/function/function.h"
#include "../../../include/evaluator/instructions/instructions.h"

void OrganizeFunctionTokens(function_t* function) {
    // list_t* -> instruction_t*
    list_t* resultInstructions = CreateDynamicList();
    instruction_t* currentInstruction = NULL;

    for (int i = 0; i < function->body->used; i++) {
        token_t* token = function->body->items[i];

        if (token->type == Word && IsStringInstruction(token->string) == 1) {
            if (currentInstruction != NULL) {
                ListAppend(resultInstructions, currentInstruction);
            }

            currentInstruction = Instruction_Create(token->string);
        } else if (currentInstruction != NULL) {
            ListAppend(currentInstruction->arguments, token);
        } else {
            DestroyToken(token);
        }
    }

    if (currentInstruction != NULL) {
        ListAppend(resultInstructions, currentInstruction);
    }

    ListFree(function->body, 0);
    function->body = resultInstructions;
}

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

    for (int i = 0; i < organizedFunctions->used; i++) {
        OrganizeFunctionTokens(organizedFunctions->items[i]);
    }

    return organizedFunctions;
}