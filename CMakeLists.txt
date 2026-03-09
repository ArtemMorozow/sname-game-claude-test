cmake_minimum_required(VERSION 3.20)
project(snake LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

find_package(SDL2 REQUIRED)

add_executable(snake
    src/main.cpp
    src/Snake.cpp
    src/Food.cpp
    src/Game.cpp
    src/Renderer.cpp
)

target_include_directories(snake PRIVATE src)

if(TARGET SDL2::SDL2)
    target_link_libraries(snake PRIVATE SDL2::SDL2)
else()
    target_include_directories(snake PRIVATE ${SDL2_INCLUDE_DIRS})
    target_link_libraries(snake PRIVATE ${SDL2_LIBRARIES})
endif()

target_compile_options(snake PRIVATE
    $<$<CXX_COMPILER_ID:GNU,Clang>:-Wall -Wextra -Wpedantic>
)
