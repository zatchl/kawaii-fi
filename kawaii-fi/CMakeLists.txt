cmake_minimum_required(VERSION 3.5)

project(kawaii-fi LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets Charts DBus REQUIRED)

include_directories(src/)

cmake_policy(SET CMP0071 NEW)
set(dbus_src org.kawaiifi.Server.xml)

set_source_files_properties(org.kawaiifi.Server.xml PROPERTIES INCLUDE libkawaii-fi/access_point.h)
qt5_add_dbus_interface(dbus_src org.kawaiifi.Server.xml kawaiifi_server_interface)

add_executable(${PROJECT_NAME}
	"src/main.cpp"

	"src/scanning/access_point_scanner.cpp"
	"src/scanning/access_point_scanner.h"

	"src/ui/mainwindow.cpp"
	"src/ui/mainwindow.h"
	"src/ui/mainwindow.ui"
	"src/ui/access_point_chart.cpp"
	"src/ui/access_point_chart.h"
	"src/ui/access_point_table.cpp"
	"src/ui/access_point_table.h"
	${dbus_src}
)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets Qt5::Charts Qt5::DBus libkawaii-fi)
