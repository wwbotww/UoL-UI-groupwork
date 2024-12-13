# Minimum CMake version required
cmake_minimum_required(VERSION 3.16)

# Project information
project(WaterQualityAnalysis VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable Qt features
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON) # Ensure resource files are compiled
set(CMAKE_AUTOUIC ON)

# make sure working on project path
add_definitions(-DPROJECT_SOURCE_DIR="${CMAKE_SOURCE_DIR}")

# Find Qt6 components
find_package(Qt6 REQUIRED COMPONENTS Widgets WebEngineWidgets Charts)

# Include header file directories
include_directories(include)

# Source files
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.hpp")

# Add resource files
set(RESOURCES resources.qrc)

# Executable file
add_executable(
        water_quality_tool
        src/pages/mainwindow.cpp
        src/pages/pollutant1.cpp
        include/pages/mainwindow.h
        include/pages/pollutant1.h
        main.cpp
        ${SOURCES}
        ${HEADERS}
        ${RESOURCES}
)

# Link Qt6 libraries
target_link_libraries(water_quality_tool PRIVATE Qt6::Widgets Qt6::WebEngineWidgets Qt6::Charts)

# Translation
set(TRANSLATIONS
        translations/en_US.ts
        translations/zh_CN.ts
        translations/fr_FR.ts
)

find_package(Qt6 REQUIRED COMPONENTS LinguistTools)
qt_add_translation(QM_FILES ${TRANSLATIONS})
