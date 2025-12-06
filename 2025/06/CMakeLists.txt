add_executable(25p06 25p06.cpp)
target_include_directories(25p06 PRIVATE ${Boost_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/../../lib)
target_link_libraries(25p06 PRIVATE aoc-lib ${Boost_LIBRARIES})
