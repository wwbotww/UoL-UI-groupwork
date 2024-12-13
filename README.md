# UoL-UI-groupwork
# Water Quality Monitoring Tool

## Team Members
- **[Team Member 1]**: Shaohui Yang, 201690924
- **[Team Member 2]**: Lew Jun Keat, 201889966
- **[Team Member 3]**: Terrence Gwatipedza, 201633773
- **[Team Member 4]**: Joshua Adam Muhd Dullah, 201803554
- **[Team Member 5]**: Mohammed Tahzim, 201713162

---

## Project Overview
The **Water Quality Monitoring Tool** is a Qt-based desktop application for
visualizing UK/EU water quality data, focusing on accessibility, internationalization, and 
clear data presentation. It enables users to explore pollutant levels, compliance with safety 
standards, and environmental trends through interactive visualizations like time-series charts, 
maps, and dashboards. Key features include pollutant overviews, compliance indicators, contextual
pop-ups, and customizable filtering by location and pollutant type, helping users gain insights 
into water quality and its health and environmental implications.

---

## Setup Instructions

### Prerequisites
1. **System Requirements**:
    - Red Hat-based system (FEPS environment or equivalent)
      **Note** : To run the application in the FEPS Red Hat environment, you must 
                 install QtWebEngine manually, as the pre-installed Qt version in this environment 
                 is incomplete and does not include the necessary WebEngine module.
    - Qt development environment (tested with Qt 6.7+)

2. **Dependencies**:
    - `Qt6` libraries:
        - **QtCharts**
        - **QtWidgets**
        - **QtCore**
        - **QtWebEngine**
    - C++ compiler
    - CMake (3.16+)

3. **Project Dependencies**:
    - `csv.hpp` (CSV parsing library included in the project)
    - Google Maps API (if relevant for mapping features)

### Compilation Steps
1. Clone the repository and navigate to the project directory:
   ```bash
    mkdir build &&
    cd build &&
    cmake .. &&
    make &&
    ./water_quality_tool

## File Structure
project/
├── data/
├── include/
│   ├── pages/
│   │   ├── fluor_stats.hpp
│   │   ├── fluor_window.hpp
│   │   ├── home_window.hpp
│   │   ├── page1_window.hpp
│   │   ├── page2_window.hpp
│   │   ├── page3_window.hpp
│   ├── csv.hpp
│   ├── dataset.hpp
│   └── water_quality.hpp
├── src/
│   ├── pages/
│   │   ├── fluor_stats.cpp
│   │   ├── fluor_window.cpp
│   │   ├── home_window.cpp
│   │   ├── page1_window.cpp
│   │   ├── page2_window.cpp
│   │   ├── page3_window.cpp
│   ├── dataset.cpp
│   └── water_quality.cpp
├── html/
├── resources.qrc
├── CMakeLists.txt
├── main.cpp
└── README.md