#-------------------------------------------------------------------
# This file is part of the CMake build system for R-Type
# For the latest info, see https://github.com/legolas-tek/r-type
#
# The contents of this file are placed in the public domain. Feel
# free to make use of it in any way you like.
#-------------------------------------------------------------------

cmake_minimum_required (VERSION 3.8)

add_library (engine SHARED)

set_target_properties (engine PROPERTIES
    FRAMEWORK TRUE
)

target_include_directories (engine
    PUBLIC
    ./includes/
)

target_sources (engine
    PRIVATE
    ./sources/Entity.cpp
    ./sources/GameLoop.cpp
    ./sources/Systems/MoveSystem.cpp
    ./sources/Systems/AnimationSystem.cpp
    ./sources/Systems/LifeTimeSystem.cpp
    ./sources/Systems/DamageSystem.cpp
    ./sources/Systems/DeathSystem.cpp
    ./sources/Systems/CollisionsSystem.cpp
    ./sources/Systems/RespawnSystem.cpp
    ./sources/Systems/FollowSystem.cpp
)

install(TARGETS engine
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        FRAMEWORK DESTINATION bin
)
