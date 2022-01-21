#include "../../list/list.h"
#include "../memory/memory.h"

#ifndef ASMVM_PROGRAM_H
#define ASMVM_PROGRAM_H

typedef struct {
    list_t* functions;
    memory_t* memory;
} program_t;

void Program_Free(program_t* program);

#endif //ASMVM_PROGRAM_H
