cmake_minimum_required(VERSION 3.31)
project(test_json)

set(CMAKE_CXX_STANDARD 20)

add_library(simple_json SHARED
        simple_json/json.h
        simple_json/json_array.cpp
        simple_json/json_value.cpp
        simple_json/json_writer.cpp
        simple_json/json_reader.cpp)

add_executable(test_json main.cpp)
target_include_directories(test_json PUBLIC simple_json)
target_link_libraries(test_json PUBLIC simple_json)
