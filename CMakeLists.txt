cmake_minimum_required(VERSION 3.15)
project(SDL_Game CXX)

set(CMAKE_CXX_STANDARD 14)

find_library(SDL2 REQUIRED)
find_library(SDL2_image REQUIRED)
find_library(SDL2_ttf REQUIRED)
find_library(SDL2_mixer REQUIRED)
find_library(lua REQUIRED)

file(GLOB SOURCE_HEADER ./src/*.h )
file(GLOB SOURCE_FILES ./src/*.cpp )
file(GLOB SOURCE_COMPONENTS_HEADER ./src/components/*.h )

add_executable( SDL_Game ${SOURCE_FILES} ${SOURCE_HEADER} ${SOURCE_COMPONENTS_HEADER} )
target_link_libraries( SDL_Game SDL2 SDL2_image SDL2_ttf SDL2_mixer lua )

set(EXECUTABLE_OUTPUT_PATH "..")

set_target_properties(
        ${PROJECT_NAME}
        PROPERTIES
        OUTPUT_NAME "${PROJECT_NAME}"
        SUFFIX ".o"
)