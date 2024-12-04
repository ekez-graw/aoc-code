add_executable(p04 p04.cpp)
target_include_directories(p04 PRIVATE ${Boost_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/../lib)
target_link_libraries(p04 PRIVATE aoc-lib ${Boost_LIBRARIES})
