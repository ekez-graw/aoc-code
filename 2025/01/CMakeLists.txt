add_executable(25p01 25p01.cpp)
target_include_directories(25p01 PRIVATE ${Boost_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/../../lib)
target_link_libraries(25p01 PRIVATE aoc-lib ${Boost_LIBRARIES})
