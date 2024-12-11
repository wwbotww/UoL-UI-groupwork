# Minimum CMake version required
cmake_minimum_required(VERSION 3.16)

# Project information
project(WaterQualityAnalysis VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)



# 如果使用手动列出源文件的方式
set(SOURCES
        src/main.cpp
        src/pages/home_window.cpp
        src/pages/fluor_window.cpp  # ⚠️ 确保这个文件被包含
        src/pages/page1_window.cpp  # 其他页面
        src/pages/page2_window.cpp
        src/pages/page3_window.cpp
)



# Enable Qt features
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON) # Ensure resource files are compiled
set(CMAKE_AUTOUIC ON)

# Find Qt6 components
find_package(Qt6 REQUIRED COMPONENTS Widgets WebEngineWidgets)

# Include header file directories
include_directories(include)

# Source files
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.hpp")

# Add resource files
set(RESOURCES resources.qrc)

# Executable file
add_executable(water_quality_tool main.cpp ${SOURCES} ${HEADERS} ${RESOURCES})

# Link Qt6 libraries
target_link_libraries(water_quality_tool PRIVATE Qt6::Widgets Qt6::WebEngineWidgets)