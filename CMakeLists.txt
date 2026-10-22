cmake_minimum_required(VERSION 3.16)
project(PhoneBook LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

add_executable(PhoneBook
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    phonebookmodel.cpp
    phonebookmodel.h
    addrecorddialog.cpp
    addrecorddialog.h
)

target_link_libraries(PhoneBook PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

install(TARGETS PhoneBook RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})