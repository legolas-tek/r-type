#-------------------------------------------------------------------
# This file is part of the CMake build system for R-Type
# For the latest info, see https://github.com/legolas-tek/r-type
#
# The contents of this file are placed in the public domain. Feel
# free to make use of it in any way you like.
#-------------------------------------------------------------------

cmake_minimum_required (VERSION 3.8)

add_executable (r-type_client)

target_link_libraries (r-type_client
    PRIVATE
    asio
    sfml-graphics
)

target_sources (r-type_client
    PRIVATE
        ./sources/main.cpp
)
