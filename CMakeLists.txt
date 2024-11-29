cmake_minimum_required(VERSION 3.16)

# Project information
project(WaterQualityAnalysis VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include header files from the 'include' folder
include_directories(include)

# Automatically find all source files in the 'src' folder
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Add the executable target
add_executable(water_quality_tool main.cpp ${SOURCES})

# Add include directories for the target
target_include_directories(water_quality_tool PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Set platform-specific properties for the executable
set_target_properties(water_quality_tool PROPERTIES
        WIN32_EXECUTABLE ON
        MACOSX_BUNDLE OFF
)

# Copy the 'data' folder to the build directory after the build is complete
add_custom_command(TARGET water_quality_tool POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/data $<TARGET_FILE_DIR:water_quality_tool>/data
)