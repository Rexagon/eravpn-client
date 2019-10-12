cmake_minimum_required(VERSION 3.14)
project(eravpn-client)

set(BUILD_OUTPUT_DIR ${CMAKE_SOURCE_DIR}/build)

set(SRC src/main.cpp)

# Qt settings
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Core Quick REQUIRED)
get_target_property(_qmake_executable Qt5::qmake IMPORTED_LOCATION)
get_filename_component(_qt_bin_dir "${_qmake_executable}" DIRECTORY)
find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS "${_qt_bin_dir}")

qt5_add_resources(RESOURCES res/app.qrc)

# Specific resource files
if (WIN32)
    set(WIN_RESOURCE_FILE ${CMAKE_SOURCE_DIR}/res/app.rc)
endif()

# Executable
add_executable(app ${SRC} ${RESOURCES} ${WIN_RESOURCE_FILE})

# Properties
set_target_properties(app PROPERTIES
        CXX_STANDARD 17
        CXX_EXTENSIONS OFF
        RUNTIME_OUTPUT_DIRECTORY ${BUILD_OUTPUT_DIR})

target_link_libraries(app PRIVATE Qt5::Core Qt5::Quick)

if (WIN32)
    set(OPENVPN_INCLUDE_DIRS
            $ENV{MBEDTLS_INCLUDE_DIR}
            $ENV{TAP_WINDOWS_INCLUDE_DIR}
            $ENV{ASIO_INCLUDE_DIR}
            $ENV{LZ4_INCLUDE_DIR}
            $ENV{OPENVPN_INCLUDE_DIR})

    target_include_directories(app PRIVATE ${OPENVPN_INCLUDE_DIRS})

    set(OPENVPN_LIBRARIES
            $ENV{MBEDTLS_LIBRARY}
            $ENV{LZ4_LIBRARY})

    target_link_libraries(app PRIVATE
            ${OPENVPN_LIBRARIES}
            fwpuclnt.lib
            ws2_32.lib
            crypt32.lib
            iphlpapi.lib
            winmm.lib
            advapi32.lib
            wininet.lib
            shell32.lib
            ole32.lib
            rpcrt4.lib
            Wtsapi32.lib
            setupapi.lib
            Dwmapi.lib)

    target_compile_definitions(app PRIVATE
            _CRT_SECURE_NO_WARNINGS
            NOMINMAX
            _WIN32_WINNT=0x0600
            USE_ASIO
            ASIO_STANDALONE
            USE_MBEDTLS
            HAVE_LZ4
            TAP_WIN_COMPONENT_ID=tap0901)

    add_custom_command(TARGET app POST_BUILD
            COMMAND "${CMAKE_COMMAND}" -E
            env PATH="${_qt_bin_dir}" "${WINDEPLOYQT_EXECUTABLE}"
            --verbose 0
            --no-compiler-runtime
            --qmldir ${CMAKE_SOURCE_DIR}/res/views
            \"$<TARGET_FILE:app>\"
            COMMENT "Deploying Qt..."
            )
endif ()
