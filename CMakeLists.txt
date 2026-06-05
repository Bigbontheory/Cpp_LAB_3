cmake_minimum_required(VERSION 3.14)
project("Cpp_LAB_3")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_DIRS "src" "src/Lab 2")


add_executable(matrix_app "src/main.cpp")
target_include_directories(matrix_app PRIVATE ${SOURCE_DIRS})


include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(matrix_tests 
    "tests/Matrix_Tests.cpp" 
    "tests/SquareMatrix_Tests.cpp" 
    "tests/DiagonalMatrix_Tests.cpp" 
    "tests/TriangleMatrix_Tests.cpp"
    "tests/SparseMatrix_Tests.cpp" 
    )

target_include_directories(matrix_tests PRIVATE ${SOURCE_DIRS})


target_link_libraries(matrix_tests PRIVATE gtest_main)

include(GoogleTest)
gtest_discover_tests(matrix_tests)