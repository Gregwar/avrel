cmake_minimum_required (VERSION 2.6)
project (avrel)

set (CMAKE_CXX_FLAGS "-std=c++0x -Wall -pedantic")

set (SOURCES
    CPUBase.cpp
    CPU.cpp
    ROM.cpp
    RAM.cpp

    timing/Chrono.cpp
    timing/sleep.cpp
    args/CommandArgs.cpp
    main.cpp
    )

add_executable (avrel ${SOURCES})
