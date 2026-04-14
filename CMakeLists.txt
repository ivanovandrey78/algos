cmake_minimum_required(VERSION 3.10)
project(CPROJECTS VERSION 1.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_subdirectory(algorithms)
add_subdirectory(structures)

add_executable(main main.cpp)

target_link_libraries(main PRIVATE 
    algorithms_lib
    structures_lib 
)

target_include_directories(main
    PUBLIC
        ${CMAKE_SOURCE_DIR}/structures
        ${CMAKE_SOURCE_DIR}/random-projects
        ${CMAKE_SOURCE_DIR}/containers
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)