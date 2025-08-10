cmake_minimum_required(VERSION 3.10)
project(headertack C)

find_package(PkgConfig REQUIRED)
pkg_check_modules(NCURSES REQUIRED ncurses)

add_executable(headertack main.c)

target_compile_options(headertack PRIVATE ${NCURSES_CFLAGS_OTHER} -Wall -O2 -std=c99)

set(CMAKE_EXE_LINKER_FLAGS "-static")
target_link_libraries(headertack ${NCURSES_LIBRARIES})
target_include_directories(headertack PRIVATE ${NCURSES_INCLUDE_DIRS})