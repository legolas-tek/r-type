#-------------------------------------------------------------------
# This file is part of the CMake build system for R-Type
# For the latest info, see https://github.com/legolas-tek/r-type
#
# The contents of this file are placed in the public domain. Feel
# free to make use of it in any way you like.
#-------------------------------------------------------------------

cmake_minimum_required (VERSION 3.8)

add_library (rendering SHARED)

target_link_libraries (rendering
    PUBLIC
    raylib
    engine
)

target_include_directories (rendering
    PUBLIC
    ./includes/
    ./sources/
)

target_sources (rendering
    PRIVATE
    ./sources/Rendering.cpp
    ./sources/RenderEntity.cpp
)
