cmake_minimum_required(VERSION 3.5)
project(Interpreter)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Lexeme.h String.h Preprocessor.h main.cpp tests/testing.h Scanner.h tests/Preprocessor-tests.cpp Preprocessor.cpp Scanner.cpp
        tests/Scanner-tests.cpp Parser.cpp Parser.h tests/Parsers-tests.cpp ReversePolishNotation.h Stack.h tests/Stack-tests.cpp)
add_executable(Interpreter ${SOURCE_FILES})