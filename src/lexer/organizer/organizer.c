#include <stdlib.h>
#include "../../../include/list/list.h"
#include "../../../include/lexer/function/function.h"
#include "../../../include/evaluator/instructions/instructions.h"

/*
 * Organize the tokens into a list of instructions.
 * @param function_t* function - The function to organize.
 * @return void.
 */
void OrganizeFunctionTokens(function_t* function) {
    // Creates a dynamic list of the result instructions.
    list_t* resultInstructions = CreateDynamicList();
    instruction_t* currentInstruction = NULL;

    for (int i = 0; i < function->body->used; i++) {
        // The current token to be checked.
        token_t* token = function->body->items[i];

        if (token->type == Word && IsStringInstruction(token->string) == 1) {
            // If the token is an instruction, create a new instruction and append the current instruction to the
            // result list.
            if (currentInstruction != NULL) {
                ListAppend(resultInstructions, currentInstruction);
            }

            currentInstruction = Instruction_Create(token->string);
        } else if (currentInstruction != NULL) {
            // If the token is not an instruction, append the token to the current instruction.
            ListAppend(currentInstruction->arguments, token);
        } else {
            // Token is outside an instruction, destroy it.
            DestroyToken(token);
        }
    }

    if (currentInstruction != NULL) {
        // Append the last instruction to the result list.
        ListAppend(resultInstructions, currentInstruction);
    }

    // Destroy the old function body list and replace it with the new instruction list.
    ListFree(function->body, 0);
    function->body = resultInstructions;
}

/*
 * Organize the tokens into functions.
 * @param list_t* tokens - The tokens to organize.
 * @return list_t* - The list of functions.
 */
list_t* OrganizeTokens(list_t* tokens) {
    // Create a dynamic list of functions.
    list_t* organizedFunctions = CreateDynamicList();
    function_t* currentFunction = NULL;

    for (int i = 0; i < tokens->used; i++) {
        // The current token to be checked.
        token_t* currentToken = tokens->items[i];

        if (currentToken->type == Function) {
            // If the token is a function, create a new function and append the current function to the
            // result list.
            if (currentFunction != NULL) {
                ListAppend(organizedFunctions, currentFunction);
            }

            list_t* functionBody = CreateDynamicList();
            currentFunction = Function_Create(currentToken, functionBody);
        } else if (currentFunction != NULL) {
            // If the token is not a function, append the token to the current function.
            ListAppend(currentFunction->body, currentToken);
        } else {
            // Destroy the token, since it is not in a function.
            DestroyToken(currentToken);
        }
    }

    if (currentFunction != NULL) {
        // Append the last function to the result list.
        ListAppend(organizedFunctions, currentFunction);
    }

    for (int i = 0; i < organizedFunctions->used; i++) {
        // Organize the tokens in the functions into instructions.
        OrganizeFunctionTokens(organizedFunctions->items[i]);
    }

    return organizedFunctions;
}