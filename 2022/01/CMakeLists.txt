add_executable(22p01 22p01.cpp)
target_include_directories(22p01 PRIVATE ${Boost_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/../../lib)
target_link_libraries(22p01 PRIVATE aoc-lib ${Boost_LIBRARIES})
