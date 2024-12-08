add_executable(p09 p09.cpp)
target_include_directories(p09 PRIVATE ${Boost_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/../../lib)
target_link_libraries(p09 PRIVATE aoc-lib ${Boost_LIBRARIES})
