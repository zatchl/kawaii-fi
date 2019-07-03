cmake_minimum_required(VERSION 3.5)

project(kawaii-fi-server LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core DBus REQUIRED)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/cmake/Modules")
find_package(LibNL REQUIRED)
include_directories(${LibNL_INCLUDE_DIR} src/)

cmake_policy(SET CMP0071 NEW)

set(dbus_src org.kawaiifi.Server.xml org.kawaiifi.Server.conf)
configure_file(org.kawaiifi.Server.xml "${CMAKE_SOURCE_DIR}/kawaii-fi" COPYONLY)

qt5_add_dbus_adaptor(dbus_src
	org.kawaiifi.Server.xml
	src/server/server.h
	KawaiiFi::Server
	kawaiifi_server_adaptor
	KawaiiFiServerAdaptor
)

add_executable(${PROJECT_NAME}
	"src/main.cpp"
	"src/server/server.cpp"
	"src/server/server.h"
	"src/server/netlink/nl_wifi_scan.cpp"
	"src/server/netlink/nl_wifi_scan.h"
	"src/server/netlink/nl_wifi_parse.cpp"
	"src/server/netlink/nl_wifi_parse.h"
	"src/server/netlink/nl_wifi_command.h"
	"src/server/netlink/ieee80211.h"
	${dbus_src}
)

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::DBus ${LibNL_LIBRARIES} libkawaii-fi)
