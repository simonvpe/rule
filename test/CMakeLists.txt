# Unit testing
if (test)
  # This builds both gtest and gmock
  add_subdirectory(googletest)
  enable_testing()
  include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
  include_directories(${gmock_SOURCE_DIR}/include ${gmock_SOURCE_DIR})

  # Build all the test sources
  file(GLOB TEST_SOURCES test_*.cpp)
  add_executable(testrunner ${TEST_SOURCES})
  target_link_libraries(testrunner gtest gtest_main)
  add_test(NAME some-test COMMAND testrunner)
endif()
