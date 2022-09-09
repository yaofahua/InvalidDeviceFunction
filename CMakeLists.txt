cmake_minimum_required(VERSION 3.8)
project(InvalidDeviceFunction LANGUAGES CXX CUDA)

set(CMAKE_CUDA_STANDARD 11)
set(CMAKE_CUDA_ARCHITECTURES 20)

add_executable(main main.cc im2col.cu)
