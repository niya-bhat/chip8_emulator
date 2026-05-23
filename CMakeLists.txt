cmake_minimum_required(VERSION 3.12)
project(Chip8Emulator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})

add_executable(chip8_vm
    src/main.cpp
    src/chip8.hpp
    src/chip8.cpp
)

target_link_libraries(chip8_vm ${SDL2_LIBRARIES})