add_executable(22p03 22p03.cpp)
target_include_directories(22p03 PRIVATE ${Boost_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/../../lib)
target_link_libraries(22p03 PRIVATE aoc-lib ${Boost_LIBRARIES})
