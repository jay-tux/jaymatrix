
cmake_minimum_required (VERSION 3.6)
project(matrix)

add_executable(matrix default.c coordinates.c main.c)
target_link_libraries(matrix ncurses)
