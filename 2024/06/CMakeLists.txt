add_executable(p06 p06.cpp)
target_include_directories(p06 PRIVATE ${Boost_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/../lib)
target_link_libraries(p06 PRIVATE aoc-lib ${Boost_LIBRARIES})
