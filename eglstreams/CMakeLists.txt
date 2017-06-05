project(eglstreams)

find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(EGL REQUIRED)
find_package(LibDRM REQUIRED)

message(STATUS "EGL_INCLUDE_DIR ${EGL_INCLUDE_DIRS}")
message(STATUS "EGL_LIBRARY ${EGL_LIBRARIES}")

set(SOURCE_FILES main.c egl.c eglgears.c kms.c utils.c)
set(HEADER_FILES egl.h eglgears.h kms.h utils.h)
add_executable(${PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -g)
target_include_directories(${PROJECT_NAME} PRIVATE  ${SDL2_INCLUDE_DIR} ${EGL_INCLUDE_DIRS} ${LIBDRM_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY} ${GLEW_LIBRARY} ${OPENGL_LIBRARY} ${EGL_LIBRARIES} ${LIBDRM_LIBRARY})
