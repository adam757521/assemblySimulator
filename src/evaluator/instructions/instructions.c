#include <string.h>
#include <stdint.h>
#include "../../../include/evaluator/instructions/instructions.h"
#include "../../../include/lexer/utils/utils.h"
#include "../../../include/errors/errors.h"
#include "../../../include/syscalls/syscalls.h"
#include "../../../include/lexer/function/function.h"
#include "../../../include/evaluator/evaluator.h"

typedef void(*instruction_f)(instruction_t*, program_t*);
const char* instructions[] = {"mov", "mem", "syscall", "call", "add", "sub", "cmp", "jmp", "jle", "inc"};

instruction_t* Instruction_Create(const char* type) {
    instruction_t* instruction = malloc(sizeof(instruction_t));
    instruction->type = type;
    instruction->arguments = CreateDynamicList();
    return instruction;
}

int IsStringInstruction(const char* string) {
    for (int i = 0; i < sizeof(instructions) / sizeof(char*); i++) {
        if (strcmp(string, instructions[i]) == 0) {
            return 1;
        }
    }

    return 0;
}

void Instruction_Free(instruction_t* instruction) {
    FreeTokenList(instruction->arguments);
    free(instruction);
}

void Instruction_InstructionMov(instruction_t* instruction, program_t* program) {
    void* dest = Program_GetMemoryByToken(program, instruction->arguments->items[0]);
    Assert(dest != NULL, "ERROR: Destination not found");

    token_t* srcToken = instruction->arguments->items[1];
    void* src = Program_GetMemoryByToken(program, srcToken);

    int copySize = 8;
    if (src != NULL) {
        copySize = Memory_GetMemorySize(program->memory, src);
    }

    memcpy(dest, src == NULL ? &srcToken->pointer : src, copySize);
}

void Instruction_InstructionMem(instruction_t* instruction, program_t* program) {
    token_t* variableName = instruction->arguments->items[0];
    token_t* variableSize = instruction->arguments->items[1];

    int64_t* size = NULL;
    if (variableSize->type == Word) {
        size = Program_GetMemoryByToken(program, variableSize);
    } else if (variableSize->type == Number) {
        size = (int64_t*)&variableSize->number;
    }

    Assert(variableName->type == Word, "ERROR: Variable name must be a word.");
    Assert(size != NULL, "ERROR: Variable size must be a number.");

    Program_AddVariable(program, variableName->string, (int)*size);
}

void Instruction_InstructionCall(instruction_t* instruction, program_t* program) {
    token_t* functionName = instruction->arguments->items[0];

    Assert(functionName->type == Word, "ERROR: Function name must be a word.");
    for (int i = 0; i < program->functions->used; i++) {
        function_t* function = program->functions->items[i];

        if (strcmp(function->definitionToken->string, functionName->string) == 0) {
            RunFunction(function, program);
        }
    }
}

void Instruction_InstructionAdd(instruction_t* instruction, program_t* program) {
    token_t* dest = instruction->arguments->items[0];
    token_t* src = instruction->arguments->items[1];

    Assert(dest->type == Word, "ERROR: Destination must be a word.");

    int64_t* destValue = Program_GetMemoryByToken(program, dest);
    int64_t* srcValue = Program_GetMemoryByToken(program, src);
    // TODO: make this safe.

    Assert(destValue != NULL, "ERROR: Destination not found.");

    if (srcValue == NULL) {
        srcValue = (int64_t*)&src->number;
    }

    *destValue += *srcValue;
}

void Instruction_InstructionSub(instruction_t* instruction, program_t* program) {
    token_t* dest = instruction->arguments->items[0];
    token_t* src = instruction->arguments->items[1];

    Assert(dest->type == Word, "ERROR: Destination must be a word.");

    int64_t* destValue = Program_GetMemoryByToken(program, dest);
    int64_t* srcValue = Program_GetMemoryByToken(program, src);

    Assert(destValue != NULL, "ERROR: Destination not found.");

    if (srcValue == NULL) {
        srcValue = (int64_t*)&src->number;
    }

    *destValue -= *srcValue;
}

void Instruction_InstructionCmp(instruction_t* instruction, program_t* program) {
    token_t* dest = instruction->arguments->items[0];
    token_t* src = instruction->arguments->items[1];

    int64_t* destPtr = Program_GetMemoryByToken(program, dest);
    int64_t* srcPtr = Program_GetMemoryByToken(program, src);

    int64_t destValue = destPtr ? Program_GetMemoryValue(program, destPtr) : dest->number;
    int64_t srcValue = srcPtr ? Program_GetMemoryValue(program, srcPtr) : src->number;

    char flag;

    if (destValue == srcValue) {
        flag = 0;
    } else if (destValue > srcValue) {
        flag = 1;
    } else {
        flag = -1;
    }

    *(char*)program->registers->items[8] = flag;
}

void Instruction_InstructionJmp(instruction_t* instruction, program_t* program) {
    Instruction_InstructionCall(instruction, program);
}

void Instruction_InstructionJle(instruction_t* instruction, program_t* program) {
    char* compareFlag = program->registers->items[8];

    if (*compareFlag <= 0) {
        Instruction_InstructionJmp(instruction, program);
    }
}

void Instruction_InstructionInc(instruction_t* instruction, program_t* program) {
    token_t* dest = instruction->arguments->items[0];

    void* destValue = Program_GetMemoryByToken(program, dest);
    Assert(destValue != NULL, "ERROR: Destination not found.");

    // Safe set memory
    // (can also dereference the pointer with a pointer pointing to an int64_t but that can write to the wrong memory)
    Program_SetMemoryValue(program, destValue, Program_GetMemoryValue(program, destValue) + 1);
}

const instruction_f instruction_functions[] = {
        Instruction_InstructionMov,
        Instruction_InstructionMem,
        Syscall,
        Instruction_InstructionCall,
        Instruction_InstructionAdd,
        Instruction_InstructionSub,
        Instruction_InstructionCmp,
        Instruction_InstructionJmp,
        Instruction_InstructionJle,
        Instruction_InstructionInc
};

void Instruction_Call(instruction_t* instruction, program_t* program) {
    for (int i = 0; i < sizeof(instruction_functions) / sizeof(instruction_f); i++) {
        if (strcmp(instruction->type, instructions[i]) == 0) {
            instruction_functions[i](instruction, program);
        }
    }
}