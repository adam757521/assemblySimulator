#include "../../list/list.h"

#ifndef ASMVM_LEXER_UTILS_UTILS_H
#define ASMVM_LEXER_UTILS_UTILS_H

void AppendChar(char *str, char c);
void FreeTokenList(list_t* tokens);
#endif