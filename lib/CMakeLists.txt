# lib/CMakeLists.txt
add_library(aoc-lib STATIC aoc-lib.cpp)

target_include_directories(aoc-lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Link Boost libraries if found
if(Boost_FOUND)
  target_link_libraries(aoc-lib ${Boost_LIBRARIES})
endif()
