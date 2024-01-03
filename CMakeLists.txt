cmake_minimum_required(VERSION 3.26)
project(DonkeyKong)

set(CMAKE_CXX_STANDARD 17)

#set(PROJ_SOURCE_DIR C:/Users/admin/OneDrive/Pulpit/DonkeyKong)
set(SDL2_DIR ${CMAKE_SOURCE_DIR}/sdl/cmake/)

#include_directories(${CMAKE_SOURCE_DIR}/sdl/include)

add_executable(DonkeyKong src/main.cpp
        src/Other.h
        src/Other.cpp
        src/Defines.h
        src/Magic.h
        src/Magic.h
        src/Magic.cpp
        src/Animation.h
        src/Animation.cpp
        src/Drawing.h
        src/Drawing.cpp
        src/MainFunctions.h
        src/MainFunctions.cpp
        src/Ladders.h
        src/Ladders.cpp)

find_package(SDL2 REQUIRED)

#set(SDL2_LIBRARIES ${PROJ_SOURCE_DIR}/sdl/lib/x64/SDL2.lib ${CMAKE_SOURCE_DIR}/sdl/lib/x64/SDL2main.lib)

#link_directories(${PROJ_SOURCE_DIR}/sdl/lib)

target_link_libraries(DonkeyKong SDL2::SDL2 SDL2::SDL2main)

add_custom_command(TARGET DonkeyKong POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/static ${CMAKE_CURRENT_BINARY_DIR}/static
)

add_custom_command(TARGET DonkeyKong POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "C:/Users/admin/OneDrive/Pulpit/DonkeyKong/sdl/lib/x64/SDL2.dll"
        $<TARGET_FILE_DIR:DonkeyKong>)