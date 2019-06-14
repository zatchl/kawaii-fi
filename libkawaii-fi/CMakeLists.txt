cmake_minimum_required(VERSION 3.5)

project(libkawaii-fi LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core REQUIRED)

add_library(${PROJECT_NAME} SHARED
	"src/accesspoint.cpp"
	"include/${PROJECT_NAME}/accesspoint.h"
	"src/wirelessinterface.cpp"
	"include/${PROJECT_NAME}/wirelessinterface.h")

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include/)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core)
