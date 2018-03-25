cmake_minimum_required(VERSION 3.8)
set (CMAKE_CXX_STANDARD 14)
set(PROJECT_NAME app)
set(CMAKE_PREFIX_PATH /home/dima/Qt/5.10.1/gcc_64)

find_package(Qt5Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)

add_executable(Main
        QT/main.cpp
        QT/player-board.cpp
        QT/two-board-window.cpp
        QT/button.cpp

        QT/button.h
        QT/player-board.h
        QT/two-board-window.h
        game.h
        QT/computer-window.cpp
        QT/computer-window.h
        QT/computer-board.cpp
        QT/computer-board.h
        QT/main-page.cpp
        QT/main-page.h)

add_executable(TextGame
        TextGame/main.cpp
        TextGame/view.h
        game.h)

include_directories(${Qt5Widgets_INCLUDES})
target_link_libraries(Main Qt5::Widgets)
