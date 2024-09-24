cmake_minimum_required(VERSION 3.10)
project(calculate_test C CXX)

set(CMAKE_C_STANDARD 90)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find GoogleTest
find_package(GTest REQUIRED)

# Add the test executable
#add_executable(calculate_test calculate_test.cpp ../calculate_module.c)
add_executable(calculate_test calculate_test.cpp
	       ../calculate_module.c
	       ../calculate.c
	       ../gcd.c
)

# Include directories for the calculate_test target
target_include_directories(calculate_test PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/mock
    ${CMAKE_CURRENT_SOURCE_DIR}/..     # Include parent directory for headers
    ${GTEST_INCLUDE_DIRS}
)

# Define UNIT_TEST for the calculate_test target
target_compile_definitions(calculate_test PRIVATE UNIT_TEST)

# Add code coverage flags
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(calculate_test PRIVATE --coverage)
    target_link_options(calculate_test PRIVATE --coverage)
endif()

# Link with GTest and pthread
target_link_libraries(calculate_test PRIVATE GTest::gtest GTest::gtest_main pthread)
