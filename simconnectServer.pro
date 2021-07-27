QT += core gui network positioning widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++latest

RC_ICONS = ../SimconnectServerIcon.ico

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    FlightplanReader/flightplanreader.cpp \
    common/binaryutil.cpp \
    main.cpp \
    mainwindow/clientfunctions/clientdisconnected.cpp \
    mainwindow/clientfunctions/quitfromclient.cpp \
    mainwindow/clientfunctions/receiveddatafromclient.cpp \
    mainwindow/mainwindow.cpp \
    mainwindow/miscfunctions/clearflightplan.cpp \
    mainwindow/miscfunctions/initserver.cpp \
    mainwindow/miscfunctions/newincomingconnection.cpp \
    mainwindow/miscfunctions/readflightplan.cpp \
    mainwindow/miscfunctions/readnewflightplan.cpp \
    mainwindow/simfunctions/closesim.cpp \
    mainwindow/simfunctions/quitfromsim.cpp \
    mainwindow/simfunctions/showsimmsg.cpp \
    mainwindow/simfunctions/simconnected.cpp \
    mainwindow/simfunctions/simconnectfailed.cpp \
    mainwindow/simfunctions/startsim.cpp \
    simconnectInterface/aircraftData/engineDataDefs.cpp \
    simconnectInterface/aircraftData/miscDataDefs.cpp \
    simconnectInterface/aircraftData/pfdDataDefs.cpp \
    simconnectInterface/dataHandlers/handleairspeeddata.cpp \
    simconnectInterface/dataHandlers/handlealtimeterdata.cpp \
    simconnectInterface/dataHandlers/handleapinfodata.cpp \
    simconnectInterface/dataHandlers/handleattitudedata.cpp \
    simconnectInterface/dataHandlers/handlebottombardata.cpp \
    simconnectInterface/dataHandlers/handlehsibrgdata.cpp \
    simconnectInterface/dataHandlers/handlehsidata.cpp \
    simconnectInterface/dataHandlers/handlejetdata.cpp \
    simconnectInterface/dataHandlers/handlenavinfodata.cpp \
    simconnectInterface/dataHandlers/handlepropdata.cpp \
    simconnectInterface/dataHandlers/handleradiodata.cpp \
    simconnectInterface/dataHandlers/handleslowdata.cpp \
    simconnectInterface/dataHandlers/handlestringsdata.cpp \
    simconnectInterface/dataHandlers/handleturbopropdata.cpp \
    simconnectInterface/dataHandlers/handlewinddata.cpp \
    simconnectInterface/getdispatches.cpp \
    simconnectInterface/readshareddata.cpp \
    simconnectInterface/rundataloop.cpp \
    simconnectInterface/sendblankenginedata.cpp \
    simconnectInterface/sendblankpfddata.cpp \
    simconnectInterface/setupaircraftdata.cpp \
    simconnectInterface/setupdata.cpp \
    simconnectInterface/simconnectthread.cpp \
    simconnectInterface/tryconnecting.cpp

HEADERS += \
    FlightplanReader/flightplanreader.h \
    common/binaryutil.h \
    common/dataIdentifiers.h \
    mainwindow/mainwindow.h \
    simconnectInterface/aircraftData/engineDataDefs.h \
    simconnectInterface/aircraftData/miscDataDefs.h \
    simconnectInterface/aircraftData/pfdDataDefs.h \
    simconnectInterface/aircraftData/sharedStructs.h \
    simconnectInterface/simconnectthread.h \
    simconnectInterface/simconnectthread.ih

FORMS += \
    mainwindow/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/'../../../../../MSFS SDK/SimConnect SDK/lib/' -lSimConnect
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/'../../../../../MSFS SDK/SimConnect SDK/lib/' -lSimConnect

INCLUDEPATH += $$PWD/'../../../../../MSFS SDK/SimConnect SDK/include'
DEPENDPATH += $$PWD/'../../../../../MSFS SDK/SimConnect SDK/include'

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/'../../../../../MSFS SDK/SimConnect SDK/lib/libSimConnect.a'
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/'../../../../../MSFS SDK/SimConnect SDK/lib/libSimConnect.a'
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/'../../../../../MSFS SDK/SimConnect SDK/lib/SimConnect.lib'
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/'../../../../../MSFS SDK/SimConnect SDK/lib/SimConnect.lib'

