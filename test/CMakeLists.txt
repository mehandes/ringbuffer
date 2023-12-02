add_subdirectory("${PROJECT_SOURCE_DIR}/extern/googletest" "extern/googletest")

add_executable(ringbuffer_tests ringbuffer_test.cc)
target_link_libraries(ringbuffer_tests ringbuffer gtest gtest_main)

gtest_discover_tests(ringbuffer_tests)
add_test(ringbuffer_tests ringbuffer_tests)