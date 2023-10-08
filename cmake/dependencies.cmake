#-------------------------------------------------------------------
# This file is part of the CMake build system for R-Type
# For the latest info, see https://github.com/legolas-tek/r-type
#
# The contents of this file are placed in the public domain. Feel
# free to make use of it in any way you like.
#-------------------------------------------------------------------

cmake_minimum_required (VERSION 3.8)

include (FetchContent)

FetchContent_Declare (asio
    GIT_REPOSITORY  https://github.com/chriskohlhoff/asio.git
    GIT_SHALLOW     TRUE
    SOURCE_DIR      ${CMAKE_CURRENT_SOURCE_DIR}/libs/deps/
)

FetchContent_GetProperties (asio)

if (NOT asio_POPULATED)
    message (STATUS "Fetching asio ${ASIO_CMAKE_ASIO_TAG}")

    if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/libs/deps/asio")
        set (FETCHCONTENT_SOURCE_DIR_ASIO "${CMAKE_CURRENT_SOURCE_DIR}/libs/deps/")
        message (STATUS "Asio sources found at ${CMAKE_CURRENT_SOURCE_DIR}/libs/deps/, skip fetching")
    endif ()

    FetchContent_Populate (asio)
    message (STATUS "Populating Asio done, sources at ${asio_SOURCE_DIR}")
endif ()

add_library (asio INTERFACE)

target_include_directories (asio
    INTERFACE ${asio_SOURCE_DIR}/asio/include
)

target_include_directories (asio
    INTERFACE ${asio_SOURCE_DIR}/asio/include
)

target_compile_definitions (asio
    INTERFACE
        ASIO_STANDALONE
        ASIO_NO_DEPRECATED
)

if (UNIX)
    target_link_libraries (asio
        INTERFACE pthread
    )
endif ()

FetchContent_Declare(raylib
    GIT_REPOSITORY "https://github.com/raysan5/raylib.git"
    GIT_TAG "master"
    GIT_PROGRESS TRUE
)

set(BUILD_SHARED_LIBS ON)

FetchContent_MakeAvailable(raylib)
