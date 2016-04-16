cmake_minimum_required(VERSION 3.5)
project(Interpretator)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Scanner.cpp Lexeme.h String.h preprocessor.h main.cpp tests/testing.h tests/String-tests.cpp tests/Lexeme-tests.cpp)
add_executable(Interpretator ${SOURCE_FILES})