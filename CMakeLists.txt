cmake_minimum_required(VERSION 3.21)
project(mechanism)

set(CMAKE_CXX_STANDARD 17)

set(DEP ${PROJECT_SOURCE_DIR}/lib)

# Header files
set(HEADER_FILES
    mechanism/mechanism.h
)

# Source files
set(SOURCE_FILES
    main.cpp
    ${DEP}/glad/src/glad.c
    mechanism/mechanism.cpp

        mechanism/engine/window.cpp mechanism/engine/window.h mechanism/environment.cpp mechanism/environment.cpp mechanism/environment.h)

# Include
include_directories(${DEP}/glfw/include)
include_directories(${DEP}/glad/include)
include_directories(${DEP}/include/) # Header-only Libraries

# Link
link_directories(${PROJECT_SOURCE_DIR}/dependencies/glfw/lib-mingw-w64)

add_executable(mechanism ${SOURCE_FILES} ${HEADER_FILES})
