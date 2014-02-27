cmake_minimum_required (VERSION 2.6)
project (EmulAVR)

set (SOURCES
    ROM.cpp

    args/CommandArgs.cpp
    main.cpp
    )

add_executable (EmulAVR ${SOURCES})
