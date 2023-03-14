cmake_minimum_required(VERSION 3.23)

project(HuaweiContest)

set(CMAKE_CXX_STANDARD 14)

add_executable(
        HuaweiContest

        main.cpp
        data_form.hpp
        huawei_io.h
        huawei_io.cpp
        Planning.cpp Planning.h Navigation.cpp Navigation.h)