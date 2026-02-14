cmake_minimum_required(VERSION 3.10)
project(CPROJECTS VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(algorithms)
add_subdirectory(structures)

add_executable(main main.cpp)

target_link_libraries(main PRIVATE 
    algorithms_lib
    structures_lib 
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)