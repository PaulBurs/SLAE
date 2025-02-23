cmake_minimum_required(VERSION 3.20)
project(MatrixBenchmark)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

# Режим Release по умолчанию
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Подключаем GTest для всех тестов
find_package(GTest REQUIRED)

# Общие настройки для всего проекта
include_directories(
    include
    ${CMAKE_CURRENT_SOURCE_DIR}/src  # Если есть заголовки в src, которые используются между модулями
)

# Основная библиотека или исполняемый файл ======================================
add_executable(tridiagonal_solver
    src/3_diagonal_matrix_solution.cpp
)

# Если tridiagonal_solver используется в тестах как библиотека:
# add_library(tridiagonal_solver_lib STATIC
#     src/3_diagonal_matrix_solution.cpp
# )
# target_include_directories(tridiagonal_solver_lib PUBLIC include)

# Тесты ========================================================================
# CSR vs Dense Matrix Benchmark
add_executable(matrix_benchmark
    test/csr_vs_dense_matrix.cpp
)

target_link_libraries(matrix_benchmark 
    PRIVATE 
    GTest::GTest 
    GTest::Main
    # tridiagonal_solver_lib  # Если используется общая библиотека
)

target_compile_options(matrix_benchmark PRIVATE -O3 -march=native)

# QR Test
add_executable(QR_decomposition_test
    test/QR_decomposition_test.cpp
)


add_executable(QR_decision_test
    test/QR_decision_test.cpp
)

add_executable(iterations_method_versus
    test/iter_method_versus.cpp
)



target_link_libraries(QR_decomposition_test
    PRIVATE 
    GTest::GTest 
    GTest::Main
    # tridiagonal_solver_lib  # Если используется общая библиотека
)

target_link_libraries(QR_decision_test 
    PRIVATE 
    GTest::GTest 
    GTest::Main
    # tridiagonal_solver_lib  # Если используется общая библиотека
)


# Автоматическая регистрация тестов
enable_testing()
add_test(NAME matrix_benchmark COMMAND matrix_benchmark)
add_test(NAME QR_decomposition_test COMMAND QR_decomposition_test)
add_test(NAME QR_decision_test COMMAND QR_decision_test)
add_test(NAME iter_method_versus COMMAND iter_method_versus)

















