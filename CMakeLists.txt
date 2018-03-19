cmake_minimum_required(VERSION 3.8)

set(PROJECT_NAME app)

find_package(Qt5Widgets)

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
        QT/computer-board.h QT/MainPage.cpp QT/MainPage.h)

include_directories(${Qt5Widgets_INCLUDES})
target_link_libraries(Main Qt5::Widgets)

add_executable(TextGame
            TextGame/main.cpp
        TextGame/main.cpp)