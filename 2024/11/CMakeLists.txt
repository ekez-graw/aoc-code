add_executable(p11 p11.cpp)
target_include_directories(p11 PRIVATE ${Boost_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/../../lib)
target_link_libraries(p11 PRIVATE aoc-lib ${Boost_LIBRARIES})
