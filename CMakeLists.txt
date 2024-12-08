# Include the user-specific configuration file
include(${CMAKE_CURRENT_SOURCE_DIR}/UserConfig.cmake OPTIONAL)

cmake_minimum_required(VERSION 3.7)
project(AOC)

# Set the build type if not specified
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

if(MSVC)
  # Set to use dynamic libraries
  set(Boost_USE_STATIC_LIBS ON)
  set(Boost_USE_MULTITHREADED ON) # Use the multithreaded libraries
  set(Boost_USE_STATIC_RUNTIME ON)
  set(BOOST_ALL_DYN_LINK OFF)

  if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
  else()
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
  endif()
endif()

# Find Boost
find_package(Boost 1.83 REQUIRED COMPONENTS system program_options filesystem)

# If Boost was found, include and link it
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
endif()

add_subdirectory(lib)

if(TARGET_DIR)
  add_subdirectory(${TARGET_DIR})
else()
  add_subdirectory(2024)
endif()

# Add flags to strip symbols for Release builds
if(NOT CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -s")
endif()
