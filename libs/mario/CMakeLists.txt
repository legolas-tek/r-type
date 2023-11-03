#-------------------------------------------------------------------
# This file is part of the CMake build system for R-Type
# For the latest info, see https://github.com/legolas-tek/r-type
#
# The contents of this file are placed in the public domain. Feel
# free to make use of it in any way you like.
#-------------------------------------------------------------------

cmake_minimum_required (VERSION 3.8)

add_library ( mario SHARED)

set_target_properties ( mario PROPERTIES
    FRAMEWORK TRUE
)

option (DEBUG_LOG_DIFF "Enable logging component diffs to a file" OFF)

if (DEBUG_LOG_DIFF)
    target_compile_definitions ( mario
        PRIVATE
        DEBUG_LOG_DIFF
    )
endif (DEBUG_LOG_DIFF)

target_link_libraries ( mario
    PUBLIC
    engine
    rendering
    networking
)

target_include_directories ( mario
    PRIVATE
    ./sources/
)

target_sources ( mario
    PRIVATE
    ./sources/MarioGame.cpp
)

install(TARGETS  mario
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        FRAMEWORK DESTINATION bin
)
