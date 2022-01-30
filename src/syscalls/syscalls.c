#include <io.h>
#include <unistd.h>
#include "../../include/evaluator/program/program.h"
#include "../../include/evaluator/instructions/instructions.h"

typedef void (*syscall_t)();

void Syscall_Print(const int* file, char **str, const int *length) {
    if (*length == 1) {
        write(*file, str, *length);
    } else {
        write(*file, *str, *length);
    }
}

void Syscall_Read(const int* file, char **str, const int *length) {
    read(*file, *str, *length);
}

void Syscall_Sleep(const int* seconds) {
    sleep(*seconds);
}

syscall_t syscallList[] = {(syscall_t) Syscall_Print, (syscall_t) Syscall_Read, (syscall_t) Syscall_Sleep};

void Syscall(instruction_t* instruction, program_t* program) {
    int* syscall = Program_GetMemory(program, instruction->arguments->items[0]);
    void* arg1 = Program_GetMemory(program, instruction->arguments->items[1]);
    void* arg2 = Program_GetMemory(program, instruction->arguments->items[2]);
    void* arg3 = Program_GetMemory(program, instruction->arguments->items[3]);

    syscallList[*syscall](arg1, arg2, arg3);
}