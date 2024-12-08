add_executable(p08 p08.cpp)
target_include_directories(p08 PRIVATE ${Boost_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/../lib)
target_link_libraries(p08 PRIVATE aoc-lib ${Boost_LIBRARIES})
