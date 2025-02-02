cmake_minimum_required(VERSION 3.10)
project(Thomas_method)

# Настройка стандарта C++ (опционально)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Создание исполняемого файла из main.cpp
add_executable(Thomas_method 3d-matrix.cpp)
