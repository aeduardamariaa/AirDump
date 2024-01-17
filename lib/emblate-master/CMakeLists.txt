# =========================================================
# Emblate

cmake_minimum_required(VERSION 3.25)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "cmake")

set(ProjectName "Emblate")
set(ProjectNamespace "Emblate")

project("${ProjectName}")

set(CMAKE_CXX_STANDARD 11)

# =========================================================
# gtest

include(FetchContent)
FetchContent_Declare(googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.13.0.zip)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

set_property(TARGET gmock PROPERTY FOLDER "gtest")
set_property(TARGET gmock_main PROPERTY FOLDER "gtest")
set_property(TARGET gtest PROPERTY FOLDER "gtest")
set_property(TARGET gtest_main PROPERTY FOLDER "gtest")

# =========================================================
# --- main
add_library(${ProjectName} INTERFACE)
add_library(${ProjectName}::${ProjectNamespace} ALIAS ${ProjectName})

target_include_directories(${ProjectName} INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:${INCLUDE_INSTALL_DIR}>)

set_target_properties(${ProjectName} PROPERTIES LINKER_LANGUAGE CXX)

# --- gtest

enable_testing()

add_executable("${ProjectName}-test"
        tests/Algorithm/test_interpolate.cpp
        tests/Algorithm/test_math.cpp
        tests/Algorithm/test_search.cpp
        tests/Algorithm/test_sort.cpp
        tests/Algorithm/test_utils.cpp
        tests/Container/test_list.cpp
        tests/Container/test_queue.cpp
        tests/Container/test_stack.cpp
        tests/Container/test_vector.cpp
)

target_link_libraries("${ProjectName}-test" gtest_main "${ProjectName}")

include(GoogleTest)
gtest_discover_tests("${ProjectName}-test")
