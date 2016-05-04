cmake_minimum_required(VERSION 3.5)
project(Interpreter)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Lexeme.h String.h Preprocessor.h main.cpp tests/testing.h Scanner.h  Preprocessor.cpp Scanner.cpp
         Parser.cpp Parser.h ReversePolishNotation.h Stack.h tests/Executor-tests.cpp Executor.h Executor.cpp )
add_executable(Interpreter ${SOURCE_FILES})