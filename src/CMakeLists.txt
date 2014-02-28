cmake_minimum_required (VERSION 2.6)
project (avrel)

set (SOURCES
    ROM.cpp

    args/CommandArgs.cpp
    main.cpp
    )

add_executable (avrel ${SOURCES})
