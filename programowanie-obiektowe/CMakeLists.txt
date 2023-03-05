cmake_minimum_required(VERSION 3.22)
project(cpp_2023_lab_01)

set(CMAKE_CXX_STANDARD 14)

# tego brakuje !! To są opcje, których ja sam używam w moich programach
# te opcje muszą być ZAWSZE włączone
add_compile_options(-Wall -Wextra)

# chcemy, by nasz kod był w pełni zgodny ze standardem
add_compile_options(-pedantic)

# zmieniamy niektóre ostrzeżenia na błędy
# missing return in non-void function: “control reaches end of non-void function"
add_compile_options(-Werror=return-type)

# misleading parentheses - read here: https://www.ibm.com/docs/en/ztpf/1.1.0.14?topic=warnings-parentheses
add_compile_options(-Werror=parentheses)

# VLA is a non-standard feature of some c++ compilers - this prevents its usage
add_compile_options(-Werror=vla)

# detect some trivial array-bounds errors in code (only compile-time !!)
add_compile_options(-Werror=array-bounds)

# additional warnings
add_compile_options ( -Wcast-qual )
add_compile_options ( -Wuninitialized )

add_executable(cpp_2023_lab_01 Student.cpp StudentBase.cpp main.cpp)
