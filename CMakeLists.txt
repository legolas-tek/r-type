#-------------------------------------------------------------------
# This file is part of the CMake build system for R-Type
# For the latest info, see https://github.com/legolas-tek/r-type
#
# The contents of this file are placed in the public domain. Feel
# free to make use of it in any way you like.
#-------------------------------------------------------------------

cmake_minimum_required (VERSION 3.8)

set (RTYPE_CMAKE_DIR "${CMAKE_CURRENT_LIST_DIR}/cmake" CACHE PATH "The path to the cmake directory")
list (APPEND CMAKE_MODULE_PATH ${RTYPE_CMAKE_DIR})

project (R-Type
    VERSION ${CMAKE_PROJECT_VERSION}
)

enable_language (CXX)
set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

include (FetchDependencies)

if (MSVC)
    include (RTypeCompilerMSVC)
else ()
    include (RTypeCompilerUnix)
endif ()

add_subdirectory (./client/)
add_subdirectory (./server/)
add_subdirectory (./tests/)

add_subdirectory (./libs/engine/)
add_subdirectory (./libs/networking/)
add_subdirectory (./libs/rendering/)
add_subdirectory (./libs/rtype/)
add_subdirectory (./libs/mario/)

include (RTypeCPackOptions)
