cmake_minimum_required(VERSION 3.2)
project(app)

# The usual stuff for QT
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
SET(CMAKE_AUTOUIC ON)
SET(CMAKE_AUTORCC ON)

# Source files
set( SRCS
    main.cpp
    widgets/mainwindow.cpp
    widgets/mainwindow.h
    widgets/mainwindow.ui
    )

# mathlib and qt libs
find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(app ${SRCS})
target_link_libraries(app gbelib Qt5::Widgets)
#install(TARGETS app DESTINATION ${PROJECT_INSTALL_BIN_DIR})

