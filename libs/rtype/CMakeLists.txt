#-------------------------------------------------------------------
# This file is part of the CMake build system for R-Type
# For the latest info, see https://github.com/legolas-tek/r-type
#
# The contents of this file are placed in the public domain. Feel
# free to make use of it in any way you like.
#-------------------------------------------------------------------

cmake_minimum_required (VERSION 3.8)

add_library (rtype SHARED)

set_target_properties (rtype PROPERTIES
    FRAMEWORK TRUE
)

target_link_libraries (rtype
    PUBLIC
    engine
    rendering
    networking
)

target_include_directories (rtype
    PRIVATE
    ./sources/
)

target_sources (rtype
    PRIVATE
    ./sources/RTypeGame.cpp
    ./sources/LobbyGame.cpp
    ./sources/Systems/AttackSystem.cpp
    ./sources/Systems/SpawnEnemySystem.cpp
    ./sources/Systems/WaveManagerSystem.cpp
    ./sources/Systems/NetworkSystem.cpp
)
