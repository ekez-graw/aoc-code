add_executable(25p05 25p05.cpp)
target_include_directories(25p05 PRIVATE ${Boost_INCLUDE_DIRS} ${CMAKE_SOURCE_DIR}/../../lib)
target_link_libraries(25p05 PRIVATE aoc-lib ${Boost_LIBRARIES})
