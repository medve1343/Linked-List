cmake_minimum_required(VERSION 3.24)
project(232_04_Lab_115)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(232_04_Lab_115
        node.h
        spy.h
        testNode.cpp
        testNode.h
        testSpy.h
        unitTest.h)
