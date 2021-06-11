QT += core gui network positioning widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++latest

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    aircraftData/engineDataDefs.cpp \
    aircraftData/miscDataDefs.cpp \
    aircraftData/pfdDataDefs.cpp \
    clientfunctions/clientdisconnected.cpp \
    clientfunctions/quitfromclient.cpp \
    clientfunctions/receiveddatafromclient.cpp \
    flightplanreader.cpp \
    main.cpp \
    mainwindow.cpp \
    miscfunctions/clearflightplan.cpp \
    miscfunctions/initserver.cpp \
    miscfunctions/newincomingconnection.cpp \
    miscfunctions/readaircraftsettings.cpp \
    miscfunctions/readflightplan.cpp \
    miscfunctions/readnewflightplan.cpp \
    simconnectInterface/dataHandlers/handlejetdata.cpp \
    simconnectInterface/dataHandlers/handlepfddata.cpp \
    simconnectInterface/dataHandlers/handlepropdata.cpp \
    simconnectInterface/dataHandlers/handleslowdata.cpp \
    simconnectInterface/dataHandlers/handlestringsdata.cpp \
    simconnectInterface/dataHandlers/handleturbopropdata.cpp \
    simconnectInterface/getdispatches.cpp \
    simconnectInterface/readshareddata.cpp \
    simconnectInterface/rundataloop.cpp \
    simconnectInterface/sendblankenginedata.cpp \
    simconnectInterface/sendblankpfddata.cpp \
    simconnectInterface/setupaircraftdata.cpp \
    simconnectInterface/setupdata.cpp \
    simconnectInterface/simconnectthread.cpp \
    simconnectInterface/tryconnecting.cpp \
    simfunctions/closesim.cpp \
    simfunctions/quitfromsim.cpp \
    simfunctions/showsimmsg.cpp \
    simfunctions/simconnected.cpp \
    simfunctions/simconnectfailed.cpp \
    simfunctions/startsim.cpp

HEADERS += \
    aircraftData/engineDataDefs.h \
    aircraftData/miscDataDefs.h \
    aircraftData/pfdDataDefs.h \
    aircraftData/sharedStructs.h \
    binaryutil.h \
    dataIdentifiers.h \
    flightplanreader.h \
    mainwindow.h \
    simconnectInterface/simconnectthread.h \
    simconnectInterface/simconnectthread.ih

FORMS += \
    mainwindow.ui

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
