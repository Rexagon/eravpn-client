# Application target
#

set(SRC
        main.cpp
        BackEnd.cpp
        Connection.cpp

        Controllers/ApplicationController.cpp
        Controllers/CertificateController.cpp
        Controllers/ClipboardController.cpp
        Controllers/ProfileController.cpp
        Controllers/ReferralClientsController.cpp
        Controllers/LocationController.cpp
        Controllers/CountriesController.cpp
        Controllers/TariffController.cpp
        Controllers/TranslationController.cpp
        Controllers/VpnController.cpp

        Models/ApplicationSettings.cpp
        Models/Certificate.cpp
        Models/CertificateListModel.cpp
        Models/Country.cpp
        Models/CountryListModel.cpp
        Models/Location.cpp
        Models/Profile.cpp
        Models/ReferralClient.cpp
        Models/ReferralClientListModel.cpp
        Models/TariffListModel.cpp
        Models/Tariff.cpp
        Models/Translation.cpp
        Models/VpnConnection.cpp

        Stuff/Logger.cpp
        Stuff/StringHelpers.cpp
        Stuff/RunGuard.cpp
        Stuff/Settings.cpp
        Stuff/Query.cpp
        Stuff/QueryBuilder.cpp)

set(SRC_MOC MocTargets.hpp)

qt5_add_resources(RESOURCES
        ${CMAKE_SOURCE_DIR}/res/app.qrc
        ${CMAKE_SOURCE_DIR}/res/flags.qrc)

# Specific resource files
if (WIN32)
    set(WIN_RESOURCES
            ${CMAKE_SOURCE_DIR}/res/app.rc
            ${CMAKE_SOURCE_DIR}/res/app.exe.manifest)
endif ()

# Build type specific options
if (CMAKE_BUILD_TYPE MATCHES Release)
    set(ADDITIONAL_DEFINES DISABLE_LOGGING)
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
        Qt5::Widgets
        Qt5::Network)

# inject properties

target_compile_definitions(app PRIVATE
        API_URL="$ENV{API_URL}"
        IPSTACK_KEY="$ENV{IPSTACK_KEY}"
        ${ADDITIONAL_DEFINES})

if (WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "/MANIFEST:NO")

    PREPEND(ABSOLUTE_SRC ${CMAKE_CURRENT_SOURCE_DIR} ${SRC})
    PREPEND(ABSOLUTE_SRC_MOC ${CMAKE_CURRENT_SOURCE_DIR} ${SRC_MOC})

    add_custom_command(TARGET app PRE_BUILD
            COMMAND "${CMAKE_COMMAND}" -E
            env PATH="${_qt_bin_dir}" "${LUPDATE_EXECUTABLE}"
            ${CMAKE_SOURCE_DIR}/res/app.qrc
            ${ABSOLUTE_SRC}
            ${ABSOLUTE_SRC_MOC}
            -ts
            ${CMAKE_SOURCE_DIR}/res/translations/main_ru.ts
            ${CMAKE_SOURCE_DIR}/res/translations/main_en.ts)

    add_custom_command(TARGET app PRE_BUILD
            COMMAND "${CMAKE_COMMAND}" -E
            env PATH="${_qt_bin_dir}" "${LRELEASE_EXECUTABLE}"
            ${CMAKE_SOURCE_DIR}/res/translations/main_ru.ts
            ${CMAKE_SOURCE_DIR}/res/translations/main_en.ts)

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
