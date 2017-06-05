cmake_minimum_required(VERSION 3.7)
project(sdl2_tut)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_COLOR_MAKEFILE   ON)

if(CMAKE_BUILD_TYPE)
    message(STATUS "Current build type: ${CMAKE_BUILD_TYPE}")
else()
    message(STATUS "Setting build to Debug")
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING
            "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif()
if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    set(CONFIG_DIR "debug" CACHE STRING "Build config directory" FORCE)
elseif(${CMAKE_BUILD_TYPE} STREQUAL "Release")
    set(CONFIG_DIR "release" CACHE STRING "Build config directory" FORCE)
elseif(${CMAKE_BUILD_TYPE} STREQUAL "MinSizeRel")
    set(CONFIG_DIR "releaseMinSize" CACHE STRING "Build config directory" FORCE)
elseif(${CMAKE_BUILD_TYPE} STREQUAL "RelWithDebInfo")
    set(CONFIG_DIR "releaseMinSize" CACHE STRING "Build config directory" FORCE)
else()
    message(FATAL_ERROR "Invalid build type: " ${CMAKE_BUILD_TYPE})
endif()

set(BUILD_BASE_DIR ${CMAKE_SOURCE_DIR}/build CACHE STRING
        "Build root directory.")
set(CMAKE_BINARY_DIR ${BUILD_BASE_DIR}/${CONFIG_DIR} CACHE STRING
        "Build directory.")
message(STATUS "Build base directory: " ${BUILD_BASE_DIR})
message(STATUS "Build config directory: " ${CMAKE_BINARY_DIR})

set(OUTPUT_BASE_DIR ${CMAKE_SOURCE_DIR}/output)
message(STATUS "Output base directory: " ${OUTPUT_BASE_DIR})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_BASE_DIR}/lib)
message(STATUS "Static lib output directory:  " ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_BASE_DIR}/bin)
message(STATUS "Dynamic lib output directory: " ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_BASE_DIR}/bin)
message(STATUS "Executable output directory:  " ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

#find_package(SDL2 REQUIRED)

add_subdirectory(SDL2-2.0.5)

set(SDL2_INCLUDE_DIR ${SDL2_BINARY_DIR}/include/ ${SDL2_SOURCE_DIR}/include/)
set(SDL2_LIBRARY SDL2main SDL2)

add_subdirectory(sdl2_engine)
add_subdirectory(sdl2_demo)
add_subdirectory(sdl2_gl)
add_subdirectory(sdl2_egl)
add_subdirectory(wayland_egl)
add_subdirectory(eglstreams)