cmake_minimum_required(VERSION 3.10)
project(My2DGame VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Add CMake modules path
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules")

# Add subdirectories
add_subdirectory(third_party)
add_subdirectory(engine)
add_subdirectory(game)
add_subdirectory(server)

# Copy assets to build directory
file(COPY assets DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
file(COPY shaders DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
