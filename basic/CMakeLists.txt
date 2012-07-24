include_directories($ENV{GTEST_DIR}/include)
include_directories(${ITA_SOURCE_DIR}/basic)
link_directories(${ITA_SOURCE_DIR}/thirdparty)

set(BASIC_TESTS list slist search-algo stack tree med-ord sort-algo)

foreach(test ${BASIC_TESTS})
  add_executable(${test}-test ${test}-test.cpp)
  target_link_libraries(${test}-test "gtest")
endforeach(test)

# more plausible usage on cmake
# set(BASIC_TESTS2 bin-tree bin-tree-search)
set(BASIC_TESTS2 bin-tree bin-tree-search br-tree)
foreach(test ${BASIC_TESTS2})
  add_executable(${test}-test ${test}-test.cpp)
  target_link_libraries(${test}-test "gtest")
endforeach(test)
