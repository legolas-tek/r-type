#-------------------------------------------------------------------
# This file is part of the CMake build system for R-Type
# For the latest info, see https://github.com/legolas-tek/r-type
#
# The contents of this file are placed in the public domain. Feel
# free to make use of it in any way you like.
#-------------------------------------------------------------------

cmake_minimum_required (VERSION 3.8)

add_library (networking SHARED)

target_link_libraries (networking
    PRIVATE
    asio
)

target_include_directories (networking
    PUBLIC
    ./includes/
    ./sources/
)

target_include_directories (networking
    PRIVATE
    ../engine/includes/
)

target_sources (networking
    PRIVATE
    ./sources/TcpNetManager.cpp
    ./sources/CircularBuffer.cpp
)

target_link_libraries (networking
    PUBLIC
    engine
)
