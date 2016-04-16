cmake_minimum_required(VERSION 2.6.1)
project(RRTUMass)

set(CMAKE_AUTOMOC ON)
SET(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

add_executable(rrt-test main.cpp mainwindow.cpp obstacles.cpp renderarea.cpp rrt.cpp)
target_link_libraries(rrt-test Qt5::Widgets Qt5::Gui)