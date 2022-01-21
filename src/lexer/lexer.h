#include "list.h"

#ifndef ASMVM_LEXER_H
#define ASMVM_LEXER_H

list_t* LexLine(const char *line, int lineNum);
list_t* LexFile(FILE* file);
#endif
