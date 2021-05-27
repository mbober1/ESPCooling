cmake_minimum_required(VERSION 3.5)
project(Cooling LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)


find_package(Qt5Widgets)
find_package(Qt5SerialPort)

set(SOURCES
    src/main.cpp
    src/mainwindow.cpp
    src/connectiondialog.cpp
    src/serial.cpp
)

set(HEADERS
    include/mainwindow.h
    include/connectiondialog.h
    include/serial.hpp
)

set(UIS
    ui_mainwindow.h
    ui_connectiondialog.h
)

qt5_add_resources(SOURCES resources.qrc)
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${UIS})
target_include_directories(${PROJECT_NAME} PUBLIC include ui)

target_link_libraries(Cooling 
Qt5::Widgets 
Qt5::SerialPort
)