cmake_minimum_required(VERSION 3.20)
project(MatrixBenchmark)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Режим Release по умолчанию
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Основной исполняемый файл для решения трехдиагональной системы
add_executable(tridiagonal_solver
    src/3_diagonal_matrix_solution.cpp
)

# Подключаем заголовочные файлы для основного проекта
target_include_directories(tridiagonal_solver PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Исполняемый файл для тестов
add_executable(matrix_benchmark
    test/csr_vs_dense_matrix.cpp
)

# Подключаем заголовочные файлы для тестов
target_include_directories(matrix_benchmark PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Оптимизация для тестов
target_compile_options(matrix_benchmark PRIVATE -O3 -march=native)