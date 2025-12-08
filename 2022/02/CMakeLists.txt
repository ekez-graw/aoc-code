add_executable(22p02 22p02.cpp)
target_include_directories(22p02 PRIVATE ${Boost_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/../../lib)
target_link_libraries(22p02 PRIVATE aoc-lib ${Boost_LIBRARIES})
