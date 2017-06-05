project(sdl2_egl)

find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(EGL REQUIRED)

message(STATUS "EGL_INCLUDE_DIR ${EGL_INCLUDE_DIRS}")
message(STATUS "EGL_LIBRARY ${EGL_LIBRARIES}")

set(SOURCE_FILES main.cpp sdl2_engine.h sdl2_engine.cpp sdl2_egl.h sdl2_egl.cpp Shader.h)
add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_include_directories(${PROJECT_NAME} PRIVATE  ${SDL2_INCLUDE_DIR} ${EGL_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY} ${GLEW_LIBRARY} ${OPENGL_LIBRARY} ${EGL_LIBRARIES})

add_custom_command(TARGET ${PROJECT_NAME}
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/VertexShader.txt ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
add_custom_command(TARGET ${PROJECT_NAME}
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/FragmentShader.txt ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
