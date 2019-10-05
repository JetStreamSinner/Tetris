cmake_minimum_required(VERSION 2.6)
project(tetris)

add_executable(tetris main.cpp)

install(TARGETS tetris RUNTIME DESTINATION bin)
