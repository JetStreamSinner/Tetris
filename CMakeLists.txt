cmake_minimum_required (VERSION 3.8)
project(Tetris)

SET(CMAKE_CXX_STANDARD 14)
SET(CMAKE_INCLUDE_CURRENT_DIR ON)
SET(CMAKE_AUTOMOC ON)
SET(Qt5Widgets_DIR /home/alex/Qt/5.12.5/gcc_64/lib/cmake/Qt5Widgets)

find_package(Qt5Widgets CONFIG REQUIRED)


SET(SRC main.cpp MainWindow.cpp)

add_executable (Tetris ${SRC})
target_link_libraries(Tetris Qt5::Widgets)
