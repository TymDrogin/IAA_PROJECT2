cmake_minimum_required(VERSION 3.30)
project(IAA_PROJECT2 C)

set(CMAKE_C_STANDARD 11)

# Include the `include` directory for headers
include_directories(${CMAKE_SOURCE_DIR}/include)
# Add all `.c` files from the `src` directory as source files
file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.c)


configure_file(
        ${CMAKE_SOURCE_DIR}/test.txt  # Source file path
        ${CMAKE_BINARY_DIR}/test.txt # Destination in the build directory
        COPYONLY                     # Copy without modification
)






# Create the executable using only source files
add_executable(${PROJECT_NAME} ${SOURCES}
        include/common-defines.h
        include/helper_functions.h
        include/file-handler.h
        include/config.h)


add_executable(IAA_PROJECT src/main.c
        src/common-defines.c
        src/helper_functions.c
        src/file-handler.c
        src/config.c
)
