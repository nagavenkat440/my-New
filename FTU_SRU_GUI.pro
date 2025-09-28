QT       += core gui
QT       += network
QT      += printsupport
QT      +=serialport
QT      +=concurrent
QT +=axcontainer
CONFIG += qobject


# Add QXlsx sources
#include(QXlsx/QXlsx.pri)

# Include QXlsx
INCLUDEPATH += $$PWD/QXlsx
DEPENDPATH += $$PWD/QXlsx



greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
TEMPLATE = app

LIBS += -lNiScope
LIBS += -lgdi32 -luser32




# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


# NI-SCOPE

#32-Bit
#INCLUDEPATH += "C:/Program Files (x86)/IVI Foundation/IVI/Include"
#LIBS += -L"C:/Program Files (x86)/IVI Foundation/IVI/Lib/msc" -lniScope

# VISA
#INCLUDEPATH += "C:/Program Files (x86)/IVI Foundation/VISA/WinNT/include"
#LIBS += -L"C:/Program Files (x86)/IVI Foundation/VISA/WinNT/lib/msc" -lvisa32


INCLUDEPATH += "C:/Program Files (x86)/IVI Foundation/IVI/Include"
LIBS += -L"C:/Program Files (x86)/IVI Foundation/IVI/Lib/msc" -lniScope



#64-Bit

#INCLUDEPATH += "C:/Program Files/IVI Foundation/IVI/Include"
#LIBS += -L"C:/Program Files/IVI Foundation/IVI/Lib_x64/msc" -lniScope

## VISA
#INCLUDEPATH += "C:/Program Files/IVI Foundation/VISA/Win64/include"
#LIBS += -L"C:/Program Files/IVI Foundation/VISA/Win64/Lib_x64/msc" -lvisa64

#-----------------------USB to I2C start-----------------
#INCLUDEPATH += $$PWD/3rdparty/ftdi

## ---------- Linking ----------
## MSVC kits (Qt Creator: MSVC 32/64-bit)
#win32-msvc {
#    # Link directly against FTDI's COFF import lib
#    LIBS += $$PWD/3rdparty/ftdi/FTD2XX.lib
#}

## MinGW kits (Qt Creator: MinGW 32/64-bit)
#win32-g++ {
#    # Expect a MinGW import lib named libftd2xx.a in 3rdparty/ftdi
#    LIBS += -L$$PWD/3rdparty/ftdi -lftd2xx -lsetupapi
#}

HEADERS += \
#    3rdparty/ftdi/ftd2xx.h \
    bittest_logger.h \
    sru_logger.h

#-----------------------USB to I2C stop-----------------

INCLUDEPATH += ../../../inc


SOURCES += \
    advantechcardsinterface.cpp \
    axistag.cpp \
    bittest_logger.cpp \
    crcutility.cpp \
    dataprocessor.cpp \
    graphwidget.cpp \
    hellothread.cpp \
    logger.cpp \
    logindialog.cpp \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp \
    qserialwork.cpp \
    qserialwork_bittest.cpp \
    qserialwork_currentsensor.cpp \
    qserialwork_uport.cpp \
    reportgenerator.cpp \
    reporttemplates.cpp \
    signalgenerator.cpp \
    sru_logger.cpp \
    swipetabwidget.cpp \
    testpointdataframming.cpp

HEADERS += \
    advantechcardsinterface.h \
    axistag.h \
    bdaqctrl.h \
    crcutility.h \
    graphwidget.h \
    dataprocessor.h \
    hellothread.h \
    logger.h \
    logindialog.h \
    mainwindow.h \
    qcustomplot.h \
    qserialwork.h \
    qserialwork_bittest.h \
    qserialwork_currentsensor.h \
    qserialwork_uport.h \
    reportgenerator.h \
    reporttemplates.h \
    signalgenerator.h \
    swipetabwidget.h \
    testpointdataframming.h


FORMS += \
    logindialog.ui \
    mainwindow.ui \
    signalgenerator.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RC_ICONS = FTU_SRU_LRU_GUI_ICON.ico

#DISTFILES += \
#    Inc/Automation.BDaq.jar


#unix: LIBS += -lbiodaq

DISTFILES +=
