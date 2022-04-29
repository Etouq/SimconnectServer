cmake_minimum_required(VERSION 3.23)

project(simconnectServer VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Gui)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Positioning)

set(PROJECT_SOURCES
        FlightplanReader/flightplanreader.cpp
        common/binaryutil.cpp
        main.cpp
        mainwindow/clientfunctions/clientdisconnected.cpp
        mainwindow/clientfunctions/quitfromclient.cpp
        mainwindow/clientfunctions/receiveddatafromclient.cpp
        mainwindow/mainwindow.cpp
        mainwindow/miscfunctions/clearflightplan.cpp
        mainwindow/miscfunctions/initserver.cpp
        mainwindow/miscfunctions/newincomingconnection.cpp
        mainwindow/miscfunctions/readflightplan.cpp
        mainwindow/miscfunctions/readnewflightplan.cpp
        mainwindow/simfunctions/closesim.cpp
        mainwindow/simfunctions/quitfromsim.cpp
        mainwindow/simfunctions/showsimmsg.cpp
        mainwindow/simfunctions/simconnected.cpp
        mainwindow/simfunctions/simconnectfailed.cpp
        mainwindow/simfunctions/startsim.cpp
        simconnectInterface/aircraftData/miscDataDefs.cpp
        simconnectInterface/aircraftData/pfdDataDefs.cpp
        simconnectInterface/dataHandlers/handleairspeeddata.cpp
        simconnectInterface/dataHandlers/handlealtimeterdata.cpp
        simconnectInterface/dataHandlers/handleapinfodata.cpp
        simconnectInterface/dataHandlers/handleattitudedata.cpp
        simconnectInterface/dataHandlers/handlebottombardata.cpp
        simconnectInterface/dataHandlers/handlehsibrgdata.cpp
        simconnectInterface/dataHandlers/handlehsidata.cpp
        simconnectInterface/dataHandlers/handlejetdata.cpp
        simconnectInterface/dataHandlers/handlenavinfodata.cpp
        simconnectInterface/dataHandlers/handlepropdata.cpp
        simconnectInterface/dataHandlers/handleradiodata.cpp
        simconnectInterface/dataHandlers/handleslowdata.cpp
        simconnectInterface/dataHandlers/handlestringsdata.cpp
        simconnectInterface/dataHandlers/handleturbopropdata.cpp
        simconnectInterface/dataHandlers/handlewinddata.cpp
        simconnectInterface/getdispatches.cpp
        simconnectInterface/readcommandstring.cpp
        simconnectInterface/readshareddata.cpp
        simconnectInterface/rundataloop.cpp
        simconnectInterface/sendblankenginedata.cpp
        simconnectInterface/sendblankpfddata.cpp
        simconnectInterface/setupaircraftdata.cpp
        simconnectInterface/setupdata.cpp
        simconnectInterface/setupevents.cpp
        simconnectInterface/simconnectthread.cpp
        simconnectInterface/tryconnecting.cpp
        FlightplanReader/flightplanreader.h
        common/binaryutil.h
        common/dataIdentifiers.h
        mainwindow/mainwindow.h
        simconnectInterface/aircraftData/engineDataDefs.h
        simconnectInterface/aircraftData/miscDataDefs.h
        simconnectInterface/aircraftData/pfdDataDefs.h
        simconnectInterface/aircraftData/sharedStructs.h
        simconnectInterface/simconnectthread.h
        simconnectInterface/simconnectthread.ih
        mainwindow/mainwindow.ui
        resources.qrc
)

qt_add_executable(${PROJECT_NAME}
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
    ${APP_ICON_RESOURCE_WINDOWS}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Network
    Qt${QT_VERSION_MAJOR}::Positioning
    "C:/MSFS SDK/SimConnect SDK/lib/SimConnect.lib"
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    WIN32_EXECUTABLE TRUE
)

qt_finalize_executable(${PROJECT_NAME})
