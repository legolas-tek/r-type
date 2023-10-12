#-------------------------------------------------------------------
# This file is part of the CMake build system for R-Type
# For the latest info, see https://github.com/legolas-tek/r-type
#
# The contents of this file are placed in the public domain. Feel
# free to make use of it in any way you like.
#-------------------------------------------------------------------

cmake_minimum_required (VERSION 3.14)

include (FetchContent)
FetchContent_Declare (
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)  
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable (googletest)

enable_testing ()

add_executable (unit_tests)

target_link_libraries (unit_tests
    PRIVATE
    GTest::gtest_main
    networking
)

target_sources (unit_tests
    PRIVATE
    diffing.cpp
)

include (GoogleTest)
gtest_discover_tests (unit_tests)
