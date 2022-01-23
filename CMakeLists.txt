cmake_minimum_required(VERSION 3.21)
project(asmVM C)

set(CMAKE_C_STANDARD 11)

include_directories(src/lexer)
include_directories(src/list)

add_executable(asmVM
        src/lexer/lexer.c
        include/lexer/lexer.h
        include/lexer/token/token.h
        include/list/list.h
        src/asmsim.c src/lexer/stream/stream.c src/list/list.c include/errors/errors.h src/errors/errors.c include/lexer/utils/utils.h src/lexer/utils/utils.c src/lexer/token/token.c include/evaluator/program/program.h src/evaluator/program/program.c include/lexer/organizer/organizer.h src/lexer/organizer/organizer.c src/lexer/function/function.c include/lexer/function/function.h include/evaluator/evaluator.h src/evaluator/evaluator.c include/evaluator/memory/memory.h src/evaluator/memory/memory.c src/evaluator/stack/stack.c include/evaluator/stack/stack.h src/evaluator/instructions/instructions.c include/evaluator/instructions/instructions.h src/syscalls/syscalls.c include/syscalls/syscalls.h)
