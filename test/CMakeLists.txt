
include(FetchContent)
FetchContent_Declare(
    googletest
    DOWNLOAD_EXTRACT_TIMESTAMP true
    URL https://github.com/google/googletest/archive/refs/tags/v1.16.0.zip 
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF)
FetchContent_MakeAvailable(googletest)

add_library(test_setup INTERFACE)

enable_testing()

add_executable(
    aoc_test
    test_argparse.cpp
    test_ElfComputer.cpp
    test_days2024.cpp
)

target_include_directories(test_setup INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(
    aoc_test
    test_setup
    cxx_setup
    util_lib
    solution_lib
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(aoc_test)
