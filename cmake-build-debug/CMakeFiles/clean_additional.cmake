# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/water_quality_tool_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/water_quality_tool_autogen.dir/ParseCache.txt"
  "water_quality_tool_autogen"
  )
endif()
