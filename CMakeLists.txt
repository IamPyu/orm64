cmake_minimum_required(VERSION 3.28)
project("orm64" C)

file(GLOB sources "src/*.c" "src/*/*.c" "src/*/*/*.c")


add_executable(${CMAKE_PROJECT_NAME} ${sources})
target_link_libraries(${CMAKE_PROJECT_NAME} edit luajit ncurses raylib)
