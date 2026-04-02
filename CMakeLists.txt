cmake_minimum_required(VERSION 3.10)
project(GraviCLI)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCES
    "src/*.cpp"
    "src/*.c++"
    "main.cpp"
)

set(SFML_BUILD_WINDOW OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_GRAPHICS OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_NETWORK OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_AUDIO ON CACHE BOOL "" FORCE)

add_subdirectory(SFML)

add_executable(GraviCLI ${SOURCES})

target_include_directories(GraviCLI PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(GraviCLI PRIVATE
    SFML::Audio
)
