cmake_minimum_required(VERSION 3.23)

set(_PROJECT_NAME SimconnectServer)
set(_PROJECT_VERSION 0.1)

project(${_PROJECT_NAME} VERSION ${_PROJECT_VERSION} LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_CLANG_TIDY clang-tidy -checks=-*,clang-*)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(APP_ICON_RESOURCE_WINDOWS "${CMAKE_CURRENT_SOURCE_DIR}/resources/icon.rc")

include(src/source_files.txt)
include(qt_modules.txt)

add_compile_definitions(LOG_TO_FILE)

find_package(Qt5 COMPONENTS ${QT_MODULES} REQUIRED)
find_package(fmt)

add_executable(${_PROJECT_NAME}
#    MANUAL_FINALIZATION
    ${CPP_FILES}
    ${HPP_FILES}
    resources/resources.qrc
    qml/qml.qrc
    ${APP_ICON_RESOURCE_WINDOWS}
)

set_target_properties(${_PROJECT_NAME} PROPERTIES OUTPUT_NAME "Simconnect Server")

target_include_directories(${_PROJECT_NAME} PUBLIC
    src
)

list(TRANSFORM QT_MODULES PREPEND Qt5::)
target_link_libraries(${_PROJECT_NAME} PRIVATE
        fmt::fmt-header-only
        ${QT_MODULES}
        "C:/MSFS SDK/SimConnect SDK/lib/SimConnect.lib"
)
set_target_properties(${_PROJECT_NAME} PROPERTIES
    WIN32_EXECUTABLE TRUE
)

#qt_finalize_executable(${_PROJECT_NAME})
