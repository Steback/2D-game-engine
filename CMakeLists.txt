cmake_minimum_required(VERSION 3.15)
project(SDL_Game CXX)

set(CMAKE_CXX_STANDARD 14)

set(EXECUTABLE_OUTPUT_PATH "..")

find_package(SDL2 REQUIRED)
include_directories( ${SDL2_INCLUDE_DIR} )

set(SOURCE_FILES
        src/main.cpp
        src/Game.h src/Game.cpp
        src/Component.h
        src/Entity.h src/Entity.cpp
        )

add_executable( SDL_Game ${SOURCE_FILES} )
target_link_libraries( SDL_Game ${SDL2_LIBRARIES} )

set_target_properties(
        ${PROJECT_NAME}
        PROPERTIES
        OUTPUT_NAME "${PROJECT_NAME}"
        SUFFIX ".o"
)