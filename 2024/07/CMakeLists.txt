add_executable(p07 p07.cpp)
target_include_directories(p07 PRIVATE ${Boost_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/../lib)
target_link_libraries(p07 PRIVATE aoc-lib ${Boost_LIBRARIES})
