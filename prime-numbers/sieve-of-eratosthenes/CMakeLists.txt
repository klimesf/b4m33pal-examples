cmake_minimum_required(VERSION 3.6)
project(sieve_of_eratosthenes)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)
add_executable(sieve_of_eratosthenes ${SOURCE_FILES})