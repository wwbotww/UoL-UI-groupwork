# CMake 最小版本
cmake_minimum_required(VERSION 3.16)

# 项目信息
project(WaterQualityAnalysis VERSION 1.0.0 LANGUAGES CXX)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 启用 Qt 特性
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON) # 确保资源文件被编译
set(CMAKE_AUTOUIC ON)

# 查找 Qt6 组件
find_package(Qt6 REQUIRED COMPONENTS Widgets WebEngineWidgets)

# 包含头文件目录
include_directories(include)

# 源文件
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.hpp")

# 添加资源文件
set(RESOURCES resources.qrc)

# 可执行文件
add_executable(water_quality_tool main.cpp ${SOURCES} ${HEADERS} ${RESOURCES})

# 链接 Qt6 库
target_link_libraries(water_quality_tool PRIVATE Qt6::Widgets Qt6::WebEngineWidgets)