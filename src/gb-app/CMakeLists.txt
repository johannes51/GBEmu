cmake_minimum_required(VERSION 3.11)
project(app)

# qt libs
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

# The usual stuff for QT
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
SET(CMAKE_AUTOUIC ON)
SET(CMAKE_AUTORCC ON)

set( SRCS
    main.cpp
    widgets/mainwindow.cpp
    widgets/mainwindow.h
    widgets/mainwindow.ui
    )

add_executable(app)
target_sources(app PRIVATE ${SRCS})
target_link_libraries(app PRIVATE gbelib Qt5::Widgets)
clang_tidy(app)
install(TARGETS app RUNTIME DESTINATION CMAKE_RUNTIME_OUTPUT_DIRECTORY)

