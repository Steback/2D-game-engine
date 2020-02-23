cmake_minimum_required(VERSION 3.15)
project(SDL_Game CXX)

set(CMAKE_CXX_STANDARD 14)

set(EXECUTABLE_OUTPUT_PATH "..")

set(SOURCE_FILES ./src)

add_executable(SDL_Game src/main.cpp ${SOURCE_FILES})

set_target_properties(
        ${PROJECT_NAME}
        PROPERTIES
        OUTPUT_NAME "${PROJECT_NAME}"
        SUFFIX ".o"
)