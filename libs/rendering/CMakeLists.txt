#-------------------------------------------------------------------
# This file is part of the CMake build system for R-Type
# For the latest info, see https://github.com/legolas-tek/r-type
#
# The contents of this file are placed in the public domain. Feel
# free to make use of it in any way you like.
#-------------------------------------------------------------------

cmake_minimum_required (VERSION 3.8)

add_library (rendering SHARED)

set_target_properties (rendering PROPERTIES
    FRAMEWORK TRUE
)

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
    ./sources/Key.cpp
    ./sources/Events.cpp
    ./sources/Systems/Text.cpp
    ./sources/Systems/Focusable.cpp
    ./sources/Systems/Editable.cpp
    ./sources/Systems/Texture.cpp
    ./sources/Systems/Close.cpp
    ./sources/Systems/Mouse.cpp
)

install(TARGETS rendering
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        FRAMEWORK DESTINATION bin
)
