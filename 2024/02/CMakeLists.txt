add_executable(p02 p02.cpp)
target_include_directories(p02 PRIVATE ${Boost_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/../lib)
target_link_libraries(p02 PRIVATE aoc-lib ${Boost_LIBRARIES})
