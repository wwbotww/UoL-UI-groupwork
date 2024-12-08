cmake_minimum_required(VERSION 3.16)

# Project information
project(WaterQualityAnalysis VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable Qt features
set(CMAKE_AUTOMOC ON)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

# Include header files
include_directories(include)

# Source files
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.hpp")

# Add executable
add_executable(water_quality_tool main.cpp ${SOURCES} ${HEADERS})

# Link Qt6 libraries
target_link_libraries(water_quality_tool PRIVATE Qt6::Widgets)
