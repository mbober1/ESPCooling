QT       += core gui widgets serialport

CONFIG += c++11

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/connectiondialog.cpp \
    src/aboutdialog.cpp \
    src/serial.cpp

HEADERS += \
    include/mainwindow.h \
    include/connectiondialog.h \
    include/aboutdialog.h \
    include/serial.hpp

FORMS += \
    uic/mainwindow.ui \
    uic/connectiondialog.ui \
    uic/aboutdialog.ui

RESOURCES += \
    resources/resources.qrc

RC_ICONS = resources/icons/fan.ico


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
