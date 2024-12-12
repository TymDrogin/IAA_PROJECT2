cmake_minimum_required(VERSION 3.29)
project(IAA_PROJECT2 C)

set(CMAKE_C_STANDARD 11)

# Include the `include` directory for headers
include_directories(${CMAKE_SOURCE_DIR}/include)
# Add all `.c` files from the `src` directory as source files
file(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.c)


file(GLOB TXT_FILES "${CMAKE_SOURCE_DIR}/*.txt")

# Loop through each file and configure it
foreach(FILE ${TXT_FILES})
    get_filename_component(FILENAME ${FILE} NAME)
    configure_file(${FILE} ${CMAKE_BINARY_DIR}/${FILENAME} COPYONLY)
endforeach()






# Create the executable using only source files
add_executable(${PROJECT_NAME} ${SOURCES}
        include/common-defines.h
        include/helper_functions.h
        include/file-handler.h
        include/data.h
        include/alrogithm.h)
