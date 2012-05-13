include_directories($ENV{GTEST_DIR}/include)
include_directories(${ITA_SOURCE_DIR}/threads)
link_directories(${ITA_SOURCE_DIR}/thirdparty)

add_executable(thread_create_term thread_create_term.cpp)
add_executable(thread_join thread_join.cpp)
add_executable(thread_stack thread_stack.cpp)
add_executable(thread_mutex thread_mutex.cpp)
add_executable(thread_cond thread_cond.cpp)
