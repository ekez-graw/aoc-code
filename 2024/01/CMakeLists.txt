add_executable(p01 p01.cpp)
target_include_directories(p01 PRIVATE ${Boost_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/../lib)
target_link_libraries(p01 PRIVATE aoc-lib ${Boost_LIBRARIES})
