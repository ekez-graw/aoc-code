add_executable(p05 p05.cpp)
target_include_directories(p05 PRIVATE ${Boost_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/../../lib)
target_link_libraries(p05 PRIVATE aoc-lib ${Boost_LIBRARIES})
