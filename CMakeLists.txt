cmake_minimum_required(VERSION 3.28)
project(SFML-FLAPPY-BIRD LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(flappybird
    src/Game.cpp
    src/Game.h
    src/Globals.h
    src/Main.cpp
    src/SharedContext.h
    src/Window.cpp
    src/Window.h
    src/World.cpp
    src/World.h

    src/utils/Animation.h src/utils/Animation.cpp

    src/states/BaseState.h
    src/states/GameState.cpp
    src/states/GameState.h
    src/states/IntroState.cpp
    src/states/IntroState.h
    src/states/StateManager.cpp
    src/states/StateManager.h
    src/states/PausedState.cpp
    src/states/PausedState.h

    src/objects/Bird.h src/objects/Bird.cpp
    src/states/GameOverState.h src/states/GameOverState.cpp
)

target_compile_features(flappybird PRIVATE cxx_std_17)
target_link_libraries(flappybird PRIVATE SFML::Graphics SFML::Audio)
