add_executable(25p03 25p03.cpp)
target_include_directories(25p03 PRIVATE ${Boost_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/../../lib)
target_link_libraries(25p03 PRIVATE aoc-lib ${Boost_LIBRARIES})
