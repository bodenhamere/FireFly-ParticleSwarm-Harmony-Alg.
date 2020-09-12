cmake_minimum_required(VERSION 3.13)
project(Project4_471 C)

set(CMAKE_C_STANDARD 99)

add_executable(Project4_471 main.c PSO.c ArrayMem.h ArrayMem.c
               Functions.h Functions.c SelectFunction.c SelectFunction.h
               mt19937ar.h mt19937ar.c PSO.h FA.c FA.h HS.c HS.h Util.c Util.h)