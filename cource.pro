#-------------------------------------------------
#
# Project created by QtCreator 2018-06-05T23:04:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = course

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        Qt/main.cpp \
        Qt/MainPage.cpp \
        Qt/TwoBoardWindow.cpp \
        Qt/SingleBoardWindow.cpp \
        Qt/PlayerBoard.cpp \
        Qt/ComputerBoard.cpp \
        Qt/ComputerWindow.cpp \
        Qt/Logger.cc \
        Qt/SettingsWindow.cc \
        Qt/RulesWindow.cc \
        Model/Board.cc \

HEADERS += \
        Qt/MainPage.h \
        Model/AbstractSolver.hh \
        Model/CachedSolver.hh \
        Model/ScoringFunctions.hh \
        Model/BestFSSolver.hh \
        Qt/BoardAnimator.hh \
        Qt/SettingsWindow.hh \
        Qt/GlobalSettings.hh \
        Qt/ComputerWindow.h \
        Qt/Button.h \
        Qt/WinnerWindow.hh \
        Qt/RulesWindow.hh \
        Qt/Logger.hh \
        Qt/SingleBoardWindow.h \
        Qt/TwoBoardWindow.h \
        Qt/ComputerBoard.h \
        Qt/PlayerBoard.h \
        Qt/Animable.hh \
        Qt/HelpBoard.hh \
