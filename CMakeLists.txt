cmake_minimum_required(VERSION 3.9)
project(projet C)

set(CMAKE_C_STANDARD 99)

add_executable(projet main.c game_board.c game.c game_board.h game.h)