#include "../token/token.h"
#include "../../list/list.h"

#ifndef ASMVM_FUNCTION_H
#define ASMVM_FUNCTION_H

typedef struct {
    token_t* definitionToken;
    list_t* body;
} function_t;

void Function_Free(function_t* function);
function_t* Function_Create(token_t* definitionToken, list_t* body);

#endif //ASMVM_FUNCTION_H
