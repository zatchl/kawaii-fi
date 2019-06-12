cmake_minimum_required(VERSION 3.1)

project(kawaii-fi LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets Charts REQUIRED)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules")
find_package(LibNL REQUIRED)
include_directories(${LibNL_INCLUDE_DIR} src/)

add_executable(${PROJECT_NAME}
	"src/main.cpp"

	"src/models/accesspoint.cpp"
	"src/models/accesspoint.h"

	"src/ui/mainwindow.cpp"
	"src/ui/mainwindow.h"
	"src/ui/mainwindow.ui"
)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets Qt5::Charts ${LibNL_LIBRARIES})
