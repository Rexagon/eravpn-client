cmake_minimum_required(VERSION 3.14)
project(eravpn-client)

# General settings
#
set(BUILD_OUTPUT_DIR ${CMAKE_SOURCE_DIR}/build)

# Configure libraries
#

# Qt settings
find_package(Qt5 COMPONENTS Core Quick Network REQUIRED)
get_target_property(_qmake_executable Qt5::qmake IMPORTED_LOCATION)
get_filename_component(_qt_bin_dir "${_qmake_executable}" DIRECTORY)
find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS "${_qt_bin_dir}")

# Json settings
find_package(nlohmann_json REQUIRED)


# Include targets
#

# Required environment variables:
#   MBEDTLS_INCLUDE_DIR
#   TAP_WINDOWS_INCLUDE_DIR
#   ASIO_INCLUDE_DIR
#   LZ4_INCLUDE_DIR
#   OPENVPN_INCLUDE_DIR
#   MBEDTLS_LIBRARY
#   LZ4_LIBRARY
add_subdirectory(src/vpn)

# Required environment variables:
#   API_URL
#   IPSTACK_KEY
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_subdirectory(src/app)
