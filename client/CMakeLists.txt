#-------------------------------------------------------------------
# This file is part of the CMake build system for R-Type
# For the latest info, see https://github.com/legolas-tek/r-type
#
# The contents of this file are placed in the public domain. Feel
# free to make use of it in any way you like.
#-------------------------------------------------------------------

cmake_minimum_required (VERSION 3.8)

add_executable (r-type_client MACOSX_BUNDLE)

option(USE_MARIO "Use rtype library instead of mario" OFF)

if(USE_MARIO)
    target_link_libraries (r-type_client
        PRIVATE
        engine
        networking
        rendering
        mario
    )
else()
    target_link_libraries (r-type_client
        PRIVATE
        engine
        networking
        rendering
        rtype
    )
endif()

target_sources (r-type_client
    PRIVATE
        ./sources/main.cpp
)

install (TARGETS r-type_client DESTINATION bin)
install (DIRECTORY ${CMAKE_SOURCE_DIR}/assets DESTINATION bin)
