#ifndef ASMVM_LEXER_H
#define ASMVM_LEXER_H

#include "../list/list.h"

list_t* LexLine(const char *line, int lineNum);
list_t* LexFile(FILE* file);
#endif
