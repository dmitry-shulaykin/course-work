cmake_minimum_required(VERSION 3.8)
set(CMAKE_CXX_STANDARD 14)
set(PROJECT_NAME app)
# set(CMAKE_PREFIX_PATH /home/dima/Qt/5.10.1/gcc_64/)

find_package(Qt5Widgets REQUIRED)
find_package(Threads REQUIRED)

set(CMAKE_AUTOMOC ON)
cmake_policy(SET CMP0100 NEW)

add_definitions(-DCMAKE_C_FLAGS="-mwindows")
SET (CMAKE_CXX_FLAGS "-Wno-deprecated-declarations")

# --------------------------------------------------------------------
if(MSVC)
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
endif()

# --------------------------------------------------------------------
# Hide the console window in visual studio projects - Release
# --------------------------------------------------------------------
if(MSVC)
        set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
endif()

set(QT5_LIBS Ws2_32 opengl32 imm32 winmm)

set(QT_SOURCES 
        Qt/main.cpp
        Qt/MainPage.cpp
        Qt/MainPage.h
        Qt/TwoBoardWindow.cpp
        Qt/SingleBoardWindow.cpp
        Qt/SingleBoardWindow.h
        Qt/TwoBoardWindow.h
        Qt/PlayerBoard.cpp
        Qt/PlayerBoard.h
        Qt/ComputerBoard.cpp
        Qt/ComputerBoard.h
        Qt/ComputerWindow.cpp
        Qt/ComputerWindow.h
        Qt/Button.h
        Qt/WinnerWindow.hh
        Qt/RulesWindow.hh
        Qt/BoardAnimator.hh
        Qt/SettingsWindow.hh
        Qt/SettingsWindow.cc
        Qt/HelpBoard.hh
        Qt/RulesWindow.cc
        Qt/Animable.hh
        Qt/GlobalSettings.hh
        Qt/LinearAnimation.hh
        Qt/LinearAnimation.cc
        Qt/Button.cc
        Qt/HelpBoard.cc
        Qt/RandomBoard.cc
        Qt/RandomBoard.hh
)

set(MODEL_SOURCES
        Model/AbstractSolver.hh
        Model/CachedSolver.hh
        Model/ScoringFunctions.hh
        Model/AStarSolver.hh
        Model/Board.cc
)
add_executable(Main
        ${QT_SOURCES}
        ${MODEL_SOURCES}
        Model/BasicSolver.hh)

add_executable(Solve_Test
        ${MODEL_SOURCES} test_main.cc
)

add_executable(Perf
        ${MODEL_SOURCES} 
        Model/AstarSolverFork.hh
        comp_perf.cc
)

include_directories(${Qt5Widgets_INCLUDES})
target_link_libraries(Main Qt5::Widgets)
target_link_libraries(Main ${CMAKE_THREAD_LIBS_INIT})