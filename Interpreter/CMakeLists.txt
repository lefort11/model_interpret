cmake_minimum_required(VERSION 3.5)
project(Interpreter)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Lexeme.h String.h Scanner/preprocessor.h main.cpp tests/testing.h Scanner/Scanner.h Scanner/Preprocessor.cpp Scanner/Scanner.cpp
        Parser/Parser.cpp Parser/Parser.h Parser/ReversePolishNotation.h Stack.h Executor/Executor.cpp Executor/Executor.h)
add_executable(Interpreter ${SOURCE_FILES})