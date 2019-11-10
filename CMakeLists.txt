cmake_minimum_required(VERSION 3.15)
project(DateClass)

set(CMAKE_CXX_STANDARD 11)

add_executable(DateClass main.cpp Date.cpp Date.h DiscountCurve.cpp DiscountCurve.h Discounts.cpp)