cmake_minimum_required(VERSION 3.5)

project(kawaii-fi LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets Charts DBus Network REQUIRED)
find_package(KF5NetworkManagerQt REQUIRED)

include_directories(src/)

add_executable(${PROJECT_NAME}
	"src/main.cpp"

	"src/ui/mainwindow.cpp"
	"src/ui/mainwindow.h"
	"src/ui/mainwindow.ui"
	"src/ui/access_point_chart.cpp"
	"src/ui/access_point_chart.h"
	"src/ui/access_point_table.cpp"
	"src/ui/access_point_table.h"
	"src/ui/access_point_detail_tree.cpp"
	"src/ui/access_point_detail_tree.h"
	"src/ui/access_point_status_bar.cpp"
	"src/ui/access_point_status_bar.h"

	"src/ui/filter-menus/access_point_filter_menu.cpp"
	"src/ui/filter-menus/access_point_filter_menu.h"
	"src/ui/filter-menus/ssid_filter_menu.cpp"
	"src/ui/filter-menus/ssid_filter_menu.h"
	"src/ui/filter-menus/bssid_filter_menu.cpp"
	"src/ui/filter-menus/bssid_filter_menu.h"
	"src/ui/filter-menus/channel_width_filter_menu.cpp"
	"src/ui/filter-menus/channel_width_filter_menu.h"
	"src/ui/filter-menus/protocol_filter_menu.cpp"
	"src/ui/filter-menus/protocol_filter_menu.h"
	"src/ui/filter-menus/channel_filter_menu.cpp"
	"src/ui/filter-menus/channel_filter_menu.h"
)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Widgets Qt5::Charts Qt5::DBus KF5::NetworkManagerQt libkawaii-fi)
