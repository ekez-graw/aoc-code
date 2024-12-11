add_executable(p10 p10.cpp)
target_include_directories(p10 PRIVATE ${Boost_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/../../lib)
target_link_libraries(p10 PRIVATE aoc-lib ${Boost_LIBRARIES})
