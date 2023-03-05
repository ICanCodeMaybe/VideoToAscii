cmake_minimum_required(VERSION 3.18.1)
project(bad_apple)

set(APPLE_CPP src/main.cpp src/pngAscii.cpp)
set(APPLE_INCLUDE_DIR src/)


add_executable(${PROJECT_NAME} ${APPLE_CPP})

target_link_libraries(${PROJECT_NAME} asound)
