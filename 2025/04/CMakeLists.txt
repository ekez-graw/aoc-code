add_executable(25p04 25p04.cpp)
target_include_directories(25p04 PRIVATE ${Boost_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/../../lib)
target_link_libraries(25p04 PRIVATE aoc-lib ${Boost_LIBRARIES})
