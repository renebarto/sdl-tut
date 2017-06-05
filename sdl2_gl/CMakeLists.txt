project(sdl2_gl)

find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)

message(STATUS "SDL2 includes: ${SDL2_INCLUDE_DIR}")
message(STATUS "SDL2 lib:      ${SDL2_LIBRARY}")

set(SOURCE_FILES main.cpp sdl2_gl.h sdl2_gl.cpp Shader.h)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE ../sdl2_engine ${SDL2_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} sdl2_engine ${SDL2_LIBRARY} ${GLEW_LIBRARY} ${OPENGL_LIBRARY})

add_custom_command(TARGET ${PROJECT_NAME}
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/VertexShader.txt ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
add_custom_command(TARGET ${PROJECT_NAME}
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/FragmentShader.txt ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
