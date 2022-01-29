#include "../../include/evaluator/instructions/function/function.h"

instruction_function_t InstructionFunction_Create(int arguments_count, instruction_f callback) {
    instruction_function_t function;
    function.arguments_count = arguments_count;
    function.function = callback;
    return function;
}
