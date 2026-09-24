include(FetchContent)
FetchContent_Declare(
  doctest
  GIT_REPOSITORY https://github.com/doctest/doctest.git
  GIT_TAG        v2.5.3
  GIT_SHALLOW    TRUE
)
FetchContent_MakeAvailable(doctest)

# Add new test files here as you write them (test_vec3.cpp, test_intersect.cpp, ...).
add_executable(rt_tests
  test_main.cpp
  test_image.cpp
)
target_link_libraries(rt_tests PRIVATE rt_core doctest::doctest)
rt_set_options(rt_tests)

include(${doctest_SOURCE_DIR}/scripts/cmake/doctest.cmake)
doctest_discover_tests(rt_tests)
