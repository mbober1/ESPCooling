QT       += core gui widgets serialport

CONFIG += c++11

SOURCES += \
    src/main.cpp \
    src/mainwindow.cpp \
    src/profile_dialog.cpp \
    src/connectiondialog.cpp \
    src/aboutdialog.cpp \
    src/serial.cpp

HEADERS += \
    include/mainwindow.h \
    include/connectiondialog.h \
    include/aboutdialog.h \
    include/types.h \
    include/serial.hpp \
    include/profile_dialog.hpp

FORMS += \
    uic/profile_dialog.ui \
    uic/mainwindow.ui \
    uic/connectiondialog.ui \
    uic/aboutdialog.ui

RESOURCES += \
    resources/resources.qrc

RC_ICONS = resources/icons/fan_white.ico


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
