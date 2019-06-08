cmake_minimum_required(VERSION 3.1)

project(kawaii-fi LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(${PROJECT_NAME}
	"main.cpp"
	"mainwindow.cpp"
	"mainwindow.h"
	"mainwindow.ui"
)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets)

