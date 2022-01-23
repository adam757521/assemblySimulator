#include <io.h>
#include <unistd.h>
#include "../../include/evaluator/program/program.h"

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

void Syscall(program_t* program) {
    int* syscall = program->registers->items[0];
    void* arg1 = program->registers->items[1];
    void* arg2 = program->registers->items[2];
    void* arg3 = program->registers->items[3];

    syscallList[*syscall](arg1, arg2, arg3);
}