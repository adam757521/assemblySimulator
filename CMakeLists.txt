cmake_minimum_required(VERSION 3.21)
project(asmVM C)

set(CMAKE_C_STANDARD 11)

include_directories(src/lexer)
include_directories(src/list)

add_executable(asmVM
        src/lexer/lexer.c
        src/lexer/lexer.h
        src/lexer/token/token.h
        src/list/list.h
        src/asmsim.c src/lexer/stream/stream.c src/list/list.c src/errors/errors.h src/errors/errors.c src/lexer/utils/utils.h src/lexer/utils/utils.c src/lexer/token/token.c src/evaluator/program/program.h src/evaluator/program/program.c src/lexer/organizer/organizer.h src/lexer/organizer/organizer.c src/lexer/function/function.c src/lexer/function/function.h src/evaluator/evaluator.h src/evaluator/evaluator.c src/evaluator/memory/memory.h src/evaluator/memory/memory.c src/evaluator/stack/stack.c src/evaluator/stack/stack.h)
