cmake_minimum_required(VERSION 3.5)

project(libkawaii-fi LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core DBus REQUIRED)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules")
find_package(LibNL REQUIRED)
include_directories(${LibNL_INCLUDE_DIR})

add_library(${PROJECT_NAME} SHARED
	"include/${PROJECT_NAME}/access_point.h"
	"include/${PROJECT_NAME}/capabilities.h"
	"include/${PROJECT_NAME}/ies/information_element.h"
	"include/${PROJECT_NAME}/ies/ie_variant.h"
	"include/${PROJECT_NAME}/ies/ssid.h"
	"include/${PROJECT_NAME}/ies/ds_parameter.h"
	"include/${PROJECT_NAME}/ies/supported_rates.h"
	"include/${PROJECT_NAME}/ies/ht_capabilities.h"
	"include/${PROJECT_NAME}/ies/ht_operations.h"
	"include/${PROJECT_NAME}/ies/vht_capabilities.h"
	"include/${PROJECT_NAME}/ies/vht_operations.h"
	"include/${PROJECT_NAME}/ies/robust_security_network.h"
	"include/${PROJECT_NAME}/ies/vendor_specific.h"
	"include/${PROJECT_NAME}/ies/wpa.h"
	"include/${PROJECT_NAME}/ies/power_constraint.h"
	"include/${PROJECT_NAME}/ies/country_info.h"
	"include/${PROJECT_NAME}/ies/rm_capabilities.h"
	"include/${PROJECT_NAME}/ies/traffic_indication_map.h"
	"include/${PROJECT_NAME}/ies/erp_info.h"
	"include/${PROJECT_NAME}/ies/extended_capabilities.h"
	"include/${PROJECT_NAME}/ies/standard-items/ie_id_standard_item.h"
	"include/${PROJECT_NAME}/ies/standard-items/ie_length_standard_item.h"
	"include/${PROJECT_NAME}/channel.h"
	"include/${PROJECT_NAME}/kawaiifi.h"
	"include/${PROJECT_NAME}/util.h"
	"include/${PROJECT_NAME}/security.h"

	"src/access_point.cpp"
	"src/capabilities.cpp"
	"src/netlink/nl_parse_attr.cpp"
	"src/netlink/nl_parse_attr.h"
	"src/netlink/nl_wifi_command.h"
	"src/netlink/nl_wifi_scan.cpp"
	"src/netlink/nl_wifi_scan.h"
	"src/ies/information_element.cpp"
	"src/ies/ssid.cpp"
	"src/ies/ds_parameter.cpp"
	"src/ies/supported_rates.cpp"
	"src/ies/ht_capabilities.cpp"
	"src/ies/ht_operations.cpp"
	"src/ies/vht_capabilities.cpp"
	"src/ies/vht_operations.cpp"
	"src/ies/robust_security_network.cpp"
	"src/ies/vendor_specific.cpp"
	"src/ies/wpa.cpp"
	"src/ies/power_constraint.cpp"
	"src/ies/country_info.cpp"
	"src/ies/rm_capabilities.cpp"
	"src/ies/traffic_indication_map.cpp"
	"src/ies/erp_info.cpp"
	"src/ies/extended_capabilities.cpp"
	"src/channel.cpp"
	"src/ies/standard-items/affirmable_field_standard_item.cpp"
	"src/ies/standard-items/affirmable_field_standard_item.h"
	"src/ies/standard-items/country_info_standard_item.cpp"
	"src/ies/standard-items/country_info_standard_item.h"
	"src/ies/standard-items/erp_info_standard_item.cpp"
	"src/ies/standard-items/erp_info_standard_item.h"
	"src/ies/standard-items/extended_capabilities_standard_item.cpp"
	"src/ies/standard-items/extended_capabilities_standard_item.h"
	"src/ies/standard-items/ht_capability_standard_item.cpp"
	"src/ies/standard-items/ht_capability_standard_item.h"
	"src/ies/standard-items/ht_operation_standard_item.cpp"
	"src/ies/standard-items/ht_operation_standard_item.h"
	"src/ies/standard-items/ie_id_standard_item.cpp"
	"src/ies/standard-items/ie_length_standard_item.cpp"
	"src/ies/standard-items/power_constraint_standard_item.cpp"
	"src/ies/standard-items/power_constraint_standard_item.h"
	"src/ies/standard-items/rm_capabilities_standard_item.cpp"
	"src/ies/standard-items/rm_capabilities_standard_item.h"
	"src/ies/standard-items/rsn_standard_item.cpp"
	"src/ies/standard-items/rsn_standard_item.h"
	"src/ies/standard-items/supportable_field_standard_item.cpp"
	"src/ies/standard-items/supportable_field_standard_item.h"
	"src/ies/standard-items/supported_rates_standard_item.cpp"
	"src/ies/standard-items/supported_rates_standard_item.h"
	"src/ies/standard-items/tim_standard_item.cpp"
	"src/ies/standard-items/tim_standard_item.h"
	"src/ies/standard-items/vht_capability_standard_item.cpp"
	"src/ies/standard-items/vht_capability_standard_item.h"
	"src/ies/standard-items/vht_operation_standard_item.cpp"
	"src/ies/standard-items/vht_operation_standard_item.h"
)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core Qt5::DBus)
