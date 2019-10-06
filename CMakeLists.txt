cmake_minimum_required (VERSION 3.8)
project(Tetris)

SET(CMAKE_CXX_STANDARD 14)
SET(CMAKE_INCLUDE_CURRENT_DIR ON)
SET(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5PrintSupport REQUIRED)

SET(Qt5Widget_DIR "C:/Qt/5.12.3/msvc2017_64/lib/cmake")

SET(SRC main.cpp MainWindow.cpp)

add_executable (Tetris ${SRC})
target_link_libraries(Tetris Qt5::Widgets)
