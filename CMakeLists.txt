cmake_minimum_required(VERSION 2.6)
project(ITA)

# starts here
set(CMAKE_CXX_FLAGS "-g -wall")
set(CMAKE_LIBRARY_PATH "${ITA_SOURCE_DIR}/thirdparty")

add_subdirectory(basic)
add_subdirectory(dp)
add_subdirectory(graph)
add_subdirectory(threads)
