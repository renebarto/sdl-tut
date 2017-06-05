project(sdl2_demo)

set(SOURCE_FILES main.cpp sdl2_gl.h sdl2_demo.cpp)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE ../sdl2_engine ${SDL2_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} sdl2_engine ${SDL2_LIBRARY})
