# VPN target
#

set(VPN_SRC
        Client.cpp
        ClientBase.cpp
        Event.cpp)

add_library(vpn
        ${VPN_SRC}
        ${WIN_RESOURCES})

set_target_properties(vpn PROPERTIES
        CXX_STANDARD 17
        CXX_EXTENSIONS OFF)

if (WIN32)
    set(OPENVPN_INCLUDE_DIRS
            $ENV{MBEDTLS_INCLUDE_DIR}
            $ENV{TAP_WINDOWS_INCLUDE_DIR}
            $ENV{ASIO_INCLUDE_DIR}
            $ENV{LZ4_INCLUDE_DIR}
            $ENV{OPENVPN_INCLUDE_DIR})

    target_include_directories(vpn PUBLIC
            ${OPENVPN_INCLUDE_DIRS}
            ${CMAKE_CURRENT_SOURCE_DIR})

    set(OPENVPN_LIBRARIES
            $ENV{MBEDTLS_LIBRARY}
            $ENV{LZ4_LIBRARY})

    target_link_libraries(vpn PUBLIC
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

    target_compile_definitions(vpn PUBLIC
            _CRT_SECURE_NO_WARNINGS
            WIN32_LEAN_AND_MEAN
            NOMINMAX
            _WIN32_WINNT=0x0600
            USE_ASIO
            ASIO_STANDALONE
            USE_MBEDTLS
            HAVE_LZ4
            TAP_WIN_COMPONENT_ID=tap0901)

    if(CMAKE_BUILD_TYPE MATCHES Debug)
        target_compile_options(vpn PRIVATE /bigobj)
    endif()
endif ()

if (APPLE)
    find_library(corefoundation_lib CoreFoundation)
    find_library(systemconfiguration_lib SystemConfiguration)
    find_library(iokit_lib IOKit)

    set(OPENVPN_INCLUDE_DIRS
            $ENV{MBEDTLS_INCLUDE_DIR}
            $ENV{ASIO_INCLUDE_DIR}
            $ENV{LZ4_INCLUDE_DIR}
            $ENV{OPENVPN_INCLUDE_DIR})

    target_include_directories(vpn PUBLIC
            ${OPENVPN_INCLUDE_DIRS}
            ${CMAKE_CURRENT_SOURCE_DIR})

    set(OPENVPN_LIBRARIES
            $ENV{MBEDTLS_LIBRARY}
            $ENV{LZ4_LIBRARY})

    target_link_libraries(vpn PUBLIC
            ${OPENVPN_LIBRARIES}
            ${corefoundation_lib}
            ${systemconfiguration_lib}
            ${iokit_lib})

    target_compile_definitions(vpn PUBLIC
            USE_ASIO
            ASIO_STANDALONE
            USE_MBEDTLS
            HAVE_LZ4
            USE_TUN_BUILDER)
endif()
