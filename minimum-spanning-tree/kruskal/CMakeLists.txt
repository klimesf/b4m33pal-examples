cmake_minimum_required(VERSION 3.6)
project(kruskal)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
    CMakeLists.txt
    main.cpp)

add_executable(kruskal ${SOURCE_FILES})