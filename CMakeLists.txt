cmake_minimum_required(VERSION 3.30)
project(IAA_PROJECT2 C)

set(CMAKE_C_STANDARD 11)

# Include the `include` directory for headers
include_directories(${CMAKE_SOURCE_DIR}/include)
# Add all `.c` files from the `src` directory as source files
file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.c)
# Create the executable using only source files
add_executable(${PROJECT_NAME} ${SOURCES}
        include/common-defines.h
        include/helper_functions.h)


add_executable(IAA_PROJECT src/main.c
        src/common-defines.c
        src/helper_functions.c)
