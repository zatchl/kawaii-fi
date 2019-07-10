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
	"include/${PROJECT_NAME}/information_elements.h"
	"include/${PROJECT_NAME}/ht_capabilities.h"
	"include/${PROJECT_NAME}/ht_operations.h"
	"include/${PROJECT_NAME}/vht_capabilities.h"
	"include/${PROJECT_NAME}/vht_operations.h"
	"include/${PROJECT_NAME}/kawaiifi.h"

	"src/access_point.cpp"
	"src/information_elements.cpp"
	"src/ht_capabilities.cpp"
	"src/ht_operations.cpp"
	"src/vht_capabilities.cpp"
	"src/vht_operations.cpp"
)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core Qt5::DBus)
