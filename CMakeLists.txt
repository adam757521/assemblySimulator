cmake_minimum_required(VERSION 3.21)
project(asmVM C)

set(CMAKE_C_STANDARD 11)

include_directories(src/lexer)
include_directories(src/list)

add_executable(asmVM
        src/lexer/lexer.c
        src/lexer/lexer.h
        src/lexer/token.h
        src/list/list.h
        src/asmsim.c src/lexer/stream/stream.c src/list/list.c src/errors/errors.h src/errors/errors.c src/lexer/utils.h src/lexer/utils.c)
