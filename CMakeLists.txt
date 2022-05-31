cmake_minimum_required(VERSION 3.20)
project(Banking08)
set(CMAKE_CXX_STANDARD 23)

add_executable(Banking08 main.cpp datetime.cpp datetime.hpp Bankaccount.cpp Bankaccount.h bank.cpp bank.h owner.cpp owner.h Activity.cpp Activity.h)