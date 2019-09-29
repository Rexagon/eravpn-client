set(SRC main.cpp)

add_executable(app ${SRC})

set_target_properties(app PROPERTIES
        CXX_STANDARD 17
        CXX_EXTENSIONS OFF)

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
            setupapi.lib)

    target_compile_definitions(app PRIVATE
            _CRT_SECURE_NO_WARNINGS
            NOMINMAX
            _WIN32_WINNT=0x0600
            USE_ASIO
            ASIO_STANDALONE
            USE_MBEDTLS
            HAVE_LZ4
            TAP_WIN_COMPONENT_ID=tap0901)
endif()
