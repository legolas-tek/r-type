#-------------------------------------------------------------------
# This file is part of the CMake build system for R-Type
# For the latest info, see https://github.com/legolas-tek/r-type
#
# The contents of this file are placed in the public domain. Feel
# free to make use of it in any way you like.
#-------------------------------------------------------------------

cmake_minimum_required (VERSION 3.8)

add_library (engine SHARED)

target_include_directories (engine
    PUBLIC
    ./includes/
)

target_sources (engine
    PRIVATE
    ./sources/R-type.cpp
    ./sources/systems.cpp
)
