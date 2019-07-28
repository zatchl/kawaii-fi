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
	"include/${PROJECT_NAME}/capabilities.h"
	"include/${PROJECT_NAME}/information_element.h"
	"include/${PROJECT_NAME}/ssid.h"
	"include/${PROJECT_NAME}/ds_parameter.h"
	"include/${PROJECT_NAME}/supported_rates.h"
	"include/${PROJECT_NAME}/ht_capabilities.h"
	"include/${PROJECT_NAME}/ht_operations.h"
	"include/${PROJECT_NAME}/vht_capabilities.h"
	"include/${PROJECT_NAME}/vht_operations.h"
	"include/${PROJECT_NAME}/robust_security_network.h"
	"include/${PROJECT_NAME}/vendor_specific.h"
	"include/${PROJECT_NAME}/wpa.h"
	"include/${PROJECT_NAME}/channel.h"
	"include/${PROJECT_NAME}/kawaiifi.h"
	"include/${PROJECT_NAME}/util.h"

	"src/access_point.cpp"
	"src/capabilities.cpp"
	"src/information_element.cpp"
	"src/ssid.cpp"
	"src/ds_parameter.cpp"
	"src/supported_rates.cpp"
	"src/ht_capabilities.cpp"
	"src/ht_operations.cpp"
	"src/vht_capabilities.cpp"
	"src/vht_operations.cpp"
	"src/robust_security_network.cpp"
	"src/vendor_specific.cpp"
	"src/wpa.cpp"
	"src/channel.cpp"
)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core Qt5::DBus)
