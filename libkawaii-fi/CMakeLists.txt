cmake_minimum_required(VERSION 3.5)

project(libkawaii-fi LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core DBus REQUIRED)

add_library(${PROJECT_NAME} SHARED
	"include/${PROJECT_NAME}/access_point.h"
	"src/access_point.cpp"
	"include/${PROJECT_NAME}/ht_capabilities.h"
	"include/${PROJECT_NAME}/ht_operations.h"
	"include/${PROJECT_NAME}/vht_capabilities.h"
	"include/${PROJECT_NAME}/kawaiifi.h"
	"src/ht_capabilities.cpp"
	"src/ht_operations.cpp"
	"src/vht_capabilities.cpp"
)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core Qt5::DBus)
