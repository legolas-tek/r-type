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

option (DEBUG_LOG_DIFF "Enable logging component diffs to a file" OFF)
option (DEBUG_LOG_EVENT "Enable logging events to a file" OFF)

if (DEBUG_LOG_DIFF)
    target_compile_definitions (rtype
        PRIVATE
        DEBUG_LOG_DIFF
    )
endif (DEBUG_LOG_DIFF)

if (DEBUG_LOG_EVENT)
    target_compile_definitions (rtype
        PRIVATE
        DEBUG_LOG_EVENT
    )
endif (DEBUG_LOG_EVENT)

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
    ./sources/ScoreManager.cpp
    ./sources/Systems/AttackSystem.cpp
    ./sources/Systems/SpawnEnemySystem.cpp
    ./sources/Systems/SoundManagerSystem.cpp
    ./sources/Systems/WaveManagerSystem.cpp
    ./sources/Systems/NetworkSystem.cpp
    ./sources/Systems/DeathAnimationManager.cpp
    ./sources/Systems/LootDropManager.cpp
    ./sources/Systems/JoinButton.cpp
    ./sources/Systems/TriggerBonus.cpp
    ./sources/Systems/SpectateButton.cpp
    ./sources/Systems/StartGameButton.cpp
    ./sources/Systems/LobbyClientImpl.cpp
    ./sources/Systems/FloatingSystem.cpp
    ./sources/Systems/End.cpp
    ./sources/Systems/EndGameSystem.cpp
    ./sources/Systems/Restart.cpp
    ./sources/Systems/ScoreOnDeath.cpp
    ./sources/Systems/SoundSystem/ShootSoundSystem.cpp
    ./sources/Systems/SoundSystem/ExplosionSoundSystem.cpp
    ./sources/Systems/ProcessKeyDownEvents.cpp
    ./sources/Systems/ProcessKeyPressedEvents.cpp
)

install(TARGETS rtype
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        FRAMEWORK DESTINATION bin
)
