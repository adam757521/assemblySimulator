#include <stdio.h>
#include <string.h>
#include "../../../include/evaluator/instructions/instructions.h"
#include "../../../include/lexer/utils/utils.h"

const char* instructions[] = {"mov"};

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
    token_t* dest = instruction->arguments->items[0];
    void* reg = Program_GetRegister(program, dest);

    // TODO: create a global handler for instructions (continue work on Instruction_Call)
    if (dest->type == Word && reg == NULL) {
        printf("Error: Register %s not found\n", dest->string);
    }

    token_t* src = instruction->arguments->items[1];

    // Will probably crash if src is not a register or src is not a number
    *(long long*)reg = src->number;
}

void Instruction_Call(instruction_t* instruction, program_t* program) {
    if (strcmp(instruction->type, "mov") == 0) {
        Instruction_InstructionMov(instruction, program);
    }
}