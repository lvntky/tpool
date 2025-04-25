cmake_minimum_required(VERSION 3.10)
project(tpool VERSION 1.0.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Create the library (STATIC for now)
add_library(tpool STATIC
    src/tpool.c
)

# Set the include directory for the library
target_include_directories(tpool PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

# Installation rules
install(TARGETS tpool
    ARCHIVE DESTINATION lib
)

install(DIRECTORY include/
    DESTINATION include
    FILES_MATCHING PATTERN "*.h"
)

# Generate pkg-config file
configure_file(
    ${PROJECT_SOURCE_DIR}/tpool.pc.in
    ${CMAKE_BINARY_DIR}/tpool.pc @ONLY
)

install(FILES ${CMAKE_BINARY_DIR}/tpool.pc DESTINATION lib/pkgconfig)
