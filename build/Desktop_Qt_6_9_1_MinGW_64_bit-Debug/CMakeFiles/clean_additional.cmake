# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "BinScribe_autogen"
  "CMakeFiles\\BinScribe_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\BinScribe_autogen.dir\\ParseCache.txt"
  )
endif()
