include_directories($ENV{GTEST_DIR}/include)
include_directories(${ITA_SOURCE_DIR}/basic)
link_directories(${ITA_SOURCE_DIR}/thirdparty)

set(DP_TESTS dynprog-algo)

foreach(test ${DP_TESTS})
  add_executable(${test}-test ${test}-test.cpp)
  target_link_libraries(${test}-test "gtest")
endforeach(test)
