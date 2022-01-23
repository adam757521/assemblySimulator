#include <string.h>
#include <stdint.h>
#include "../../../include/evaluator/instructions/instructions.h"
#include "../../../include/lexer/utils/utils.h"
#include "../../../include/errors/errors.h"
#include "../../../include/syscalls/syscalls.h"
#include "../../../include/lexer/function/function.h"
#include "../../../include/evaluator/evaluator.h"

const char* instructions[] = {"mov", "mem", "syscall", "call"};

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

    uint64_t srcValue = (uint64_t) srcToken->pointer;
    memcpy(dest, src == NULL ? &srcValue : src, copySize);
}

void Instruction_InstructionMem(instruction_t* instruction, program_t* program) {
    token_t* variableName = instruction->arguments->items[0];
    token_t* variableSize = instruction->arguments->items[1];

    uint64_t* size = NULL;
    if (variableSize->type == Word) {
        size = Program_GetMemoryByToken(program, variableSize);
    } else if (variableSize->type == Number) {
        size = (uint64_t*)&variableSize->number;
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

void Instruction_Call(instruction_t* instruction, program_t* program) {
    if (strcmp(instruction->type, "mov") == 0) {
        Instruction_InstructionMov(instruction, program);
    } else if (strcmp(instruction->type, "mem") == 0) {
        Instruction_InstructionMem(instruction, program);
    } else if (strcmp(instruction->type, "syscall") == 0) {
        Syscall(program);
    } else if (strcmp(instruction->type, "call") == 0) {
        Instruction_InstructionCall(instruction, program);
    }
}