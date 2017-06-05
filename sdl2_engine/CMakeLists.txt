project(sdl2_engine)

message(STATUS "SDL2 includes: ${SDL2_INCLUDE_DIR}")
message(STATUS "SDL2 lib:      ${SDL2_LIBRARY}")
set(SOURCE_FILES sdl2_engine.h sdl2_engine.cpp)
add_library(${PROJECT_NAME} ${SOURCE_FILES})
#target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_INCLUDE_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_BINARY_DIR}/include/)
target_include_directories(${PROJECT_NAME} PRIVATE ${SDL2_SOURCE_DIR}/include/)
