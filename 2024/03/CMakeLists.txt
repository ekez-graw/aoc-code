add_executable(p03 p03.cpp)
target_include_directories(p03 PRIVATE ${Boost_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/../lib)
target_link_libraries(p03 PRIVATE aoc-lib ${Boost_LIBRARIES})
