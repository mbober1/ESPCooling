QT       += core gui widgets serialport

CONFIG += c++11

SOURCES += \
    src/hid_interface.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/connectiondialog.cpp \
    src/aboutdialog.cpp \
    src/serial.cpp \
    src/thread.cpp

HEADERS += \
    include/data_types.hpp \
    include/mainwindow.h \
    include/connectiondialog.h \
    include/aboutdialog.h \
    include/serial.hpp \
    include/hid_interface.hpp \
    include/thread.hpp

FORMS += \
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

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += hidapi-libusb
