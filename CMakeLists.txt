cmake_minimum_required(VERSION 3.14)
project("Cpp_LAB_3")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Указываем правильные пути к папкам с хедерами
# Судя по скрину, они в src и src/Lab 2
set(SOURCE_DIRS "src" "src/Lab 2")

# --- Секция приложения (UI) ---
# ВАЖНО: указываем путь src/main.cpp, так как он лежит в папке src
add_executable(matrix_app "src/main.cpp")

target_include_directories(matrix_app PRIVATE ${SOURCE_DIRS})

# --- Секция тестов (GTest) ---
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Проверь, что файлы тестов лежат в корневой папке tests/
add_executable(matrix_tests 
    "tests/Matrix_Tests.cpp" 
    "tests/SquareMatrix_Tests.cpp" 
    "tests/DiagonalMatrix_Tests.cpp" 
    "tests/TriangleMatrix_Tests.cpp"
)

target_include_directories(matrix_tests PRIVATE ${SOURCE_DIRS})
target_link_libraries(matrix_tests PRIVATE GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(matrix_tests)