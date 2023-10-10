#-------------------------------------------------------------------
# This file is part of the CMake build system for R-Type
# For the latest info, see https://github.com/legolas-tek/r-type
#
# The contents of this file are placed in the public domain. Feel
# free to make use of it in any way you like.
#-------------------------------------------------------------------

cmake_minimum_required (VERSION 3.8)

add_library (networking SHARED)

if (MSVC)
    # warning level 4
    target_compile_options (networking
        PRIVATE
        /W4
    )
else ()
    # additional warnings
    target_compile_options (networking
        PRIVATE
        -Wall -Wextra -fsanitize=address
    )
    target_link_libraries (networking
        PRIVATE
        -fsanitize=address
    )
endif ()

target_link_libraries (networking
    PUBLIC
    asio
    engine
)

target_include_directories (networking
    PUBLIC
    ./includes/
    ./sources/
)

target_sources (networking
    PRIVATE
    ./sources/TcpNetManager.cpp
    ./sources/UdpNetManager.cpp
    ./sources/CircularBuffer.cpp
    ./sources/Snapshot.cpp
    ./sources/Sync.cpp
    ./sources/NetworkServerSystem.cpp
    ./sources/NetworkClientSystem.cpp
)
