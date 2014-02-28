cmake_minimum_required (VERSION 2.6)
project (avrel)

set (CMAKE_CXX_FLAGS "-std=c++0x -Wall -pedantic")

set (SOURCES
    CPUBase.cpp
    CPU.cpp
    ROM.cpp

    timing/Chrono.cpp
    args/CommandArgs.cpp
    main.cpp
    )

add_executable (avrel ${SOURCES})
