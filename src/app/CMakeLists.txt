# Application target
#

set(SRC
        main.cpp
        BackEnd.cpp
        Connection.cpp

        Controllers/CertificateController.cpp
        Controllers/ClipboardController.cpp
        Controllers/ProfileController.cpp
        Controllers/LocationController.cpp
        Controllers/CountriesController.cpp
        Controllers/TariffController.cpp
        Controllers/VpnController.cpp

        Models/Certificate.cpp
        Models/CertificateListModel.cpp
        Models/Country.cpp
        Models/CountryListModel.cpp
        Models/Location.cpp
        Models/Profile.cpp
        Models/TariffListModel.cpp
        Models/Tariff.cpp
        Models/VpnConnection.cpp

        Stuff/StringHelpers.cpp
        Stuff/Settings.cpp
        Stuff/Query.cpp
        Stuff/QueryBuilder.cpp)

set(SRC_MOC
        BackEnd.hpp
        Connection.hpp

        Controllers/CertificateController.hpp
        Controllers/ClipboardController.hpp
        Controllers/CountriesController.hpp
        Controllers/LocationController.hpp
        Controllers/ProfileController.hpp
        Controllers/TariffController.hpp
        Controllers/VpnController.hpp

        Models/CertificateListModel.hpp
        Models/CountryListModel.hpp
        Models/Location.hpp
        Models/Profile.hpp
        Models/TariffListModel.hpp
        Models/Tariff.hpp
        Models/VpnConnection.hpp)

qt5_add_resources(RESOURCES
        ${CMAKE_SOURCE_DIR}/res/app.qrc)

# Specific resource files
if (WIN32)
    set(WIN_RESOURCES
            ${CMAKE_SOURCE_DIR}/res/app.rc
            ${CMAKE_SOURCE_DIR}/res/app.exe.manifest)

    if(CMAKE_BUILD_TYPE MATCHES Release)
        set(ADDITIONAL_EXECUTABLE_OPTIONS WIN32)
    endif()
endif ()

# Executable
add_executable(app
        ${ADDITIONAL_EXECUTABLE_OPTIONS}
        ${SRC}
        ${SRC_MOC}
        ${RESOURCES}
        ${WIN_RESOURCES})

# Properties
set_target_properties(app PROPERTIES
        CXX_STANDARD 17
        CXX_EXTENSIONS OFF
        RUNTIME_OUTPUT_DIRECTORY ${BUILD_OUTPUT_DIR})

target_link_libraries(app PRIVATE
        vpn
        Qt5::Core
        Qt5::Quick
        Qt5::Network)

# inject properties

target_compile_definitions(app PRIVATE
        API_URL="$ENV{API_URL}"
        IPSTACK_KEY="$ENV{IPSTACK_KEY}")

if (WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "/MANIFEST:NO")

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
