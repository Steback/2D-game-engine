cmake_minimum_required(VERSION 3.15)
project(2D_Game_Engine CXX)

#### Settings ####
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY $<1:${CMAKE_SOURCE_DIR}>)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY $<1:${CMAKE_SOURCE_DIR}>)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY $<1:${CMAKE_SOURCE_DIR}>)

### Third-Party Libraries ###
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)
#find_package(SDL2_mixer REQUIRED)
find_package(glm REQUIRED)
find_package(lua REQUIRED)
find_package(sol2 REQUIRED)

### Source Code ###
file(GLOB SOURCE_CODE src/*.cpp  src/*.h)

add_executable(2D_Game ${SOURCE_CODE})
target_link_libraries(2D_Game SDL2::SDL2 SDL2_image::SDL2_image sdl_ttf::sdl_ttf glm::glm lua::lua sol2::sol2)