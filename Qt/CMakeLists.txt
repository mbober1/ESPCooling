cmake_minimum_required(VERSION 3.5)
project(Cooling LANGUAGES CXX)


set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)


find_package(Qt5Widgets)

set(SOURCES
    src/main.cpp
    src/mainwindow.cpp
)

set(HEADERS
    include/mainwindow.h
)

set(UIS
    ui_mainwindow.h
    ui_connect.h
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${UIS})
target_include_directories(${PROJECT_NAME} PUBLIC include ui)

target_link_libraries(Cooling 
Qt5::Widgets 
)

# if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
#     qt_add_executable(Cooling
#         MANUAL_FINALIZATION
#         ${PROJECT_SOURCES}
#     )
# else()
#     if(ANDROID)
#         add_library(Cooling SHARED
#             ${PROJECT_SOURCES}
#         )
#     else()
#         add_executable(Cooling
#             ${PROJECT_SOURCES}
#         )
#     endif()
# endif()

# target_link_libraries(Cooling PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# set_target_properties(Cooling PROPERTIES
#     MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
#     MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
#     MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
# )

# if(QT_VERSION_MAJOR EQUAL 6)
#     qt_finalize_executable(Cooling)
# endif()
